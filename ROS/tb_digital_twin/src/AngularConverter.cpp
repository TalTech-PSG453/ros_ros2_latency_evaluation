#include <ros/ros.h>
#include <tb_digital_twin/Float32Stamped.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include "data_logger/data_logger.hpp"
#include <cmath>
#include <iostream>
using namespace DataLogger;

class AngularConverter
{
public:
    std::unique_ptr<SubscriptionLogger> p_angular_sub;
    AngularConverter()
    {
        p_angular_sub.reset(new SubscriptionLogger("/shaft_angular_velocity"));
    }
    float rpm;
    void VelocityReceiver(const tb_digital_twin::Float32Stamped::ConstPtr &msg)
    {
        rpm = msg->data*60/(2* M_PI);

        if(msg->id == p_angular_sub->next_id)
        {
            p_angular_sub->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_angular_sub->time_diffs.push_back(diff.toNSec());
        }
        p_angular_sub->next_id = msg->id + 1;
    }
    
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "angular_converter",ros::init_options::AnonymousName);
    ROS_INFO("Started angular_converter");
    ros::NodeHandle nh;
    ros::Rate rate(60);

    AngularConverter listener;
    ros::Subscriber feedbackReceiver = nh.subscribe<tb_digital_twin::Float32Stamped>("shaft_angular_velocity", 10,
                                                                       &AngularConverter::VelocityReceiver, &listener);

    ros::Publisher rotationPublish = nh.advertise<tb_digital_twin::Float32Stamped>("actual_rpm", 10);
    std::unique_ptr<PublisherLogger> p_rotation_pub;
    p_rotation_pub.reset(new PublisherLogger("/actual_rpm"));

    tb_digital_twin::Float32Stamped rpm_msg;
    rpm_msg.data = 0;
    rpm_msg.id = 0;

  while(ros::ok())
  {
      ros::spinOnce();
      rpm_msg.data = listener.rpm;
      rotationPublish.publish(rpm_msg);
      rpm_msg.id += 1;
      p_rotation_pub->sent_counter += 1;
      rate.sleep();

  }
    DataLogger::save_logged_data("angular_converter.csv");
  return 0;
}
