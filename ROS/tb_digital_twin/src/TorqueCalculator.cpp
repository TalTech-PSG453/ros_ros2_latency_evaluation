//
// Created by sejego on 2/3/21.
//
#include <ros/ros.h>
#include <iostream>
#include <tb_digital_twin/Power.h>
#include <tb_digital_twin/Float32Stamped.h>
#include "data_logger/data_logger.hpp"

using namespace DataLogger;

class TorqueCalculator
{
private:
    //const int angularVelocity = 157; // rad/s or 1500 rpm
    bool velocityUpdated = false;
    bool powerUpdated = false;
    bool efficiencyUpdated = false;

    float electricalPower, efficiency, angularVelocity;
    float mechanicalTorque = 0;
    float electricalTorqueRef = 0;

    float calculateElectricalTorqueRef()
    {
        return (electricalPower / angularVelocity);
    }

    float calculateMechanicalTorque()
    {
        return (electricalTorqueRef * efficiency);
    }


public:

    std::unique_ptr<SubscriptionLogger> p_power_rec;
    std::unique_ptr<SubscriptionLogger> p_efficiency_rec;
    std::unique_ptr<SubscriptionLogger> p_angular_rec;

    TorqueCalculator()
    {
        p_power_rec.reset(new SubscriptionLogger("/motor_power/electrical_power"));
        p_efficiency_rec.reset(new SubscriptionLogger("/efficiency"));
        p_angular_rec.reset(new SubscriptionLogger("/shaft_angular_velocity"));
    }

    float getMechanicalTorque()
    {
        return mechanicalTorque;
    }

    float getElectricalTorqueRef()
    {
        return electricalTorqueRef;
    }

    void powerListener(const tb_digital_twin::Power::ConstPtr &msg)
    {
        electricalPower = msg->total;
        if(msg->id == p_power_rec->next_id)
        {
            p_power_rec->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_power_rec->time_diffs.push_back(diff.toNSec());
        }
        p_power_rec->next_id = msg->id + 1;
        powerUpdated = true;
        if(powerUpdated && velocityUpdated)
        {
            electricalTorqueRef = calculateElectricalTorqueRef();
            powerUpdated = false;
            velocityUpdated = false;
        }
    }
    void efficiencyListener(const tb_digital_twin::Float32Stamped::ConstPtr &msg)
    {
        efficiency = msg->data;
        if(msg->id == p_efficiency_rec->next_id)
        {
            p_efficiency_rec->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_efficiency_rec->time_diffs.push_back(diff.toNSec());
        }
        p_efficiency_rec->next_id = msg->id + 1;
       // efficiencyUpdated = true;
        mechanicalTorque = calculateMechanicalTorque();
    }
    void angularVelocityListener(const tb_digital_twin::Float32Stamped::ConstPtr &msg)
    {
        angularVelocity = msg->data;
        if(msg->id == p_angular_rec->next_id)
        {
            p_angular_rec->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_angular_rec->time_diffs.push_back(diff.toNSec());
        }
        p_angular_rec->next_id = msg->id + 1;

        velocityUpdated = true;
        if(powerUpdated && velocityUpdated)
        {
            electricalTorqueRef = calculateElectricalTorqueRef();
            powerUpdated = false;
            velocityUpdated = false;
            powerUpdated = false;
        }
    }
};


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "torque_calculator",ros::init_options::AnonymousName);
    ROS_INFO("Started torque_calculator");
    ros::NodeHandle nh;
    ros::Rate rate(60);

    TorqueCalculator torqueCalculator;
    /* Subscribers */
    ros::Subscriber powerReceiver = nh.subscribe<tb_digital_twin::Power>("motor_power/electrical_power", 100,
                                                                       &TorqueCalculator::powerListener, &torqueCalculator);
    ros::Subscriber efficiencyReceiver = nh.subscribe<tb_digital_twin::Float32Stamped>("efficiency", 100,
                                                                    &TorqueCalculator::efficiencyListener, &torqueCalculator);
    ros::Subscriber angularVelocityReceiver = nh.subscribe<tb_digital_twin::Float32Stamped>("shaft_angular_velocity", 100,
                                                                              &TorqueCalculator::angularVelocityListener, &torqueCalculator);

    /* Publishers */
    ros::Publisher electricalTorquePublisher = nh.advertise<tb_digital_twin::Float32Stamped>("electrical_torque_ref", 10);
    ros::Publisher mechanicalTorquePublisher = nh.advertise<tb_digital_twin::Float32Stamped>("mechanical_torque", 10);
    std::unique_ptr<PublisherLogger> p_electrical_pub;
    std::unique_ptr<PublisherLogger> p_mechanical_pub;
    p_electrical_pub.reset(new PublisherLogger("/electrical_torque"));
    p_mechanical_pub.reset(new PublisherLogger("/mechanical_torque"));

    tb_digital_twin::Float32Stamped elec_torque_msg;
    tb_digital_twin::Float32Stamped mech_torque_msg;
    elec_torque_msg.data = 0;
    mech_torque_msg.data = 0;
    elec_torque_msg.id = 0;
    mech_torque_msg.id = 0;

    while(ros::ok())
    {
        ros::spinOnce();
        elec_torque_msg.data = torqueCalculator.getElectricalTorqueRef();
        mech_torque_msg.data = torqueCalculator.getMechanicalTorque();
        electricalTorquePublisher.publish(elec_torque_msg);
        p_electrical_pub->sent_counter += 1;
        elec_torque_msg.id += 1;
        mechanicalTorquePublisher.publish(mech_torque_msg);
        p_mechanical_pub->sent_counter += 1;
        mech_torque_msg.id += 1;
        rate.sleep();
    }
    DataLogger::save_logged_data("torque_calculator.csv");

    return 0;
}