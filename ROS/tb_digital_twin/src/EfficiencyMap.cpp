/**
 * twist_to_motors - converts a twist message to motor commands.  Needed for navigation stack
 *
 * This code is based on a similar node from the differential_drive package
 * http://wiki.ros.org/differential_drive
 * https://github.com/jfstepha/differential-drive
 * TODO: FIX THIS STUFF TO BE CORRECT
 */
#include <ros/ros.h>
#include <ros/console.h>
#include <tb_digital_twin/Float32Stamped.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "data_logger/data_logger.hpp"
using namespace std;
using namespace DataLogger;
int ticksSinceTarget;

int closestItemIDX(vector<float> array, float item)
{
    float delta=-1;
    int idx=-1;

    //cout<<array.size()<<endl;

    for (int i = 0;i<array.size();i++)
    {
        float it=array.at(i);
        if(i==0)
        {
            delta=abs(it-item);

            idx=i;
        }
        else if(delta>abs(it-item)) {

            delta = abs(it - item);
            idx=i;
        }

        //cout<<i<<endl;
    }
    return idx;
}
vector<float> rpm;
vector<vector<float>> torque;
vector<vector<float>> rmsEfficiency;
struct state{
    float rpm;
    float torque;
}current_state;

int rate;
int timeoutTicks;

class EfficiencyMapProcessor{
public:
    string line;

    std::unique_ptr<PublisherLogger> p_efficiency_pub;
    std::unique_ptr<SubscriptionLogger> p_torque_sub;
    std::unique_ptr<SubscriptionLogger> p_rpm_sub;

    EfficiencyMapProcessor(string filename)
    {
        std::ifstream file(filename);
        if(!file.is_open())
        {
            ROS_ERROR("Could not open file");
            throw std::runtime_error("Could not open file");
        }
        int line_c=0;
        int word_c=0;

        while (std::getline(file, line))
        {
            word_c=0;
            string word = "";
            vector<float> temp_tor;
            vector<float> temp_eff;
            for (auto x : line)
            {
                if (x == ',')
                {
                    if(line_c==0&&word_c%2==0)
                    {
                        //cout<<word<<endl;
                        rpm.push_back(stof(word));
                    } else if(line_c==0&&word_c%2!=0)
                    {

                    }
                    else
                    {
                        if(word_c%2==0)
                        {
                            temp_tor.push_back(stof(word));
                        }
                        else
                        {
                            temp_eff.push_back(stof(word));
                        }
                    }
                    word_c++;
                    word = "";
                }
                else
                {
                    word = word + x;
                }
            }
            if(line_c==0&&word_c%2==0)
            {
                rpm.push_back(stof(word));
            } else if(line_c==0&&word_c%2!=0)
            {
            }
            else
            {
                if(word_c%2==0)
                {
                    temp_tor.push_back(stof(word));
                }
                else
                {
                    temp_eff.push_back(stof(word));
                }
                torque.push_back(temp_tor);
                rmsEfficiency.push_back(temp_eff);
                word_c++;
            }
            line_c++;
        }
        cout<<torque.size()<<endl;
        cout<<torque.size()<<endl;

        rate=60;
        timeoutTicks=2;
        ros::NodeHandle pnode("~");
        pnode.getParam("twist_to_motor_rate", rate);
        pnode.getParam("twist_to_motor_timeout_ticks", timeoutTicks);

        // initializing publishers/subscribers
        TorqueReceiver = handler.subscribe<tb_digital_twin::Float32Stamped>("torque", 10, &EfficiencyMapProcessor::getTorque, this);
        RPMReceiver = handler.subscribe<tb_digital_twin::Float32Stamped>("actual_rpm", 10, &EfficiencyMapProcessor::getRPM, this);
        EfficiencyControl = handler.advertise<tb_digital_twin::Float32Stamped>("efficiency", 10);
        p_efficiency_pub.reset(new PublisherLogger("/efficiency"));
        p_torque_sub.reset(new SubscriptionLogger("/electrical_torque_ref"));
        p_rpm_sub.reset(new SubscriptionLogger("/actual_rpm"));

        efficiency_value.id = 0;
    }
    ~EfficiencyMapProcessor()
    {
        save_logged_data("efficiency_map.csv");
    }

    float getEfficiency(float c_rpm, float c_torque)
    {
        int idx_rpm = closestItemIDX(rpm,c_rpm);
        vector<float> torque_column;
        for(auto item : torque)
        {
            torque_column.push_back(item.at(idx_rpm));
        }
        int idx_torque=closestItemIDX(torque_column,c_torque);
        return rmsEfficiency.at(idx_torque).at(idx_rpm);
    }

    void spin() {

        ros::Rate r(rate);
        ros::Rate idle(10);
        ros::Time then = ros::Time::now();
        ros::spinOnce();
        ROS_INFO("Initialized");
        // main control loop
        while (ros::ok())
        {
            spinOnce();
            ros::spinOnce();
            idle.sleep();
        }
        ROS_INFO("Quit");
    }

    void spinOnce()
    {
        ros::spinOnce();
        efficiency_value.data = (getEfficiency(current_state.rpm,current_state.torque)/100); // *current_state.torque
        efficiency_value.stamp = ros::Time::now();
        EfficiencyControl.publish(efficiency_value);
        efficiency_value.id += 1;
        p_efficiency_pub->sent_counter += 1;
    }

private:
    ros::NodeHandle handler;
    ros::Subscriber TorqueReceiver;
    ros::Subscriber RPMReceiver;
    ros::Publisher EfficiencyControl;

    tb_digital_twin::Float32Stamped efficiency_value;

    void getTorque(const tb_digital_twin::Float32Stamped::ConstPtr& msg)
    {
        ticksSinceTarget = 0;
        current_state.torque=msg->data;
        //cout<<"Torque: "<<current_state.torque<<endl;
        if(msg->id == p_torque_sub->next_id)
            {
                p_torque_sub->recv_counter += 1;
                ros::Duration diff = ros::Time::now() - msg->stamp;
                p_torque_sub->time_diffs.push_back(diff.toNSec());
            }
            p_torque_sub->next_id = msg->id + 1;
    }
    void getRPM(const tb_digital_twin::Float32Stamped::ConstPtr& msg)
    {
        ticksSinceTarget = 0;
        current_state.rpm=msg->data;
        //cout<<"RPM: "<<current_state.rpm<<endl;
        if(msg->id == p_rpm_sub->next_id)
            {
                p_rpm_sub->recv_counter += 1;
                ros::Duration diff = ros::Time::now() - msg->stamp;
                p_rpm_sub->time_diffs.push_back(diff.toNSec());
            }
            p_rpm_sub->next_id = msg->id + 1;
    }
};

//TODO: cosine phi!!!!
int main(int argc, char **argv) {
    string filename_csv;
    ros::init(argc, argv, "efficiency_map",ros::init_options::AnonymousName);
    int compare;
    ROS_INFO("Started efficiency_map node");
    ros::param::get("~csv_file", filename_csv);

    try {
        EfficiencyMapProcessor EffMapper(filename_csv);
        EffMapper.spin();
    }
    catch (const ros::Exception &e) {
        ROS_ERROR("Error occured %s", e.what());
        return (1);
    }

    return 0;
}
