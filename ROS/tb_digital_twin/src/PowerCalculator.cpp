#include <ros/ros.h>
#include <stdlib.h>
#include <tb_digital_twin/Float32Stamped.h>
#include <tb_digital_twin/Current.h>
#include <tb_digital_twin/Voltage.h>
#include <tb_digital_twin/Power.h>

#include "data_logger/data_logger.hpp"
using namespace DataLogger;

class PowerCalculator
{
private:
    bool canCalculate = false;
    bool* const pVoltageReady = &vReady;
    bool* const pCurrentReady = &cReady;
    bool* const pCanCalculate = &canCalculate;
    float inputCurrent[3];
    float inputVoltage[3];
    float mean[2][3] ={0.0};
    float square[2][3] = {0.0};
    std::vector<std::vector<float>> currents;
    std::vector<std::vector<float>> voltages;
    std::vector<std::vector<float>> currentBuffer;
    std::vector<std::vector<float>> voltageBuffer;
    const float cosPhi = 0.84;
    const int SIZE_A = 5000;
    int c  = 0;
    int v = 0;

    void calculateRMS()
    {
        /* Square */
        for (int j = 0; j < SIZE_A; j++)
        {
            square[0][0] += currentBuffer[0][j] * currentBuffer[0][j];
            square[0][1] += currentBuffer[1][j] * currentBuffer[1][j];
            square[0][2] += currentBuffer[2][j] * currentBuffer[2][j];

            square[1][0] += voltageBuffer[0][j] * voltageBuffer[0][j];
            square[1][1] += voltageBuffer[1][j] * voltageBuffer[1][j];
            square[1][2] += voltageBuffer[2][j] * voltageBuffer[2][j];
        }
        for (int j = 0; j < 3; j++)
        {
            mean[0][j] = (square[0][j] / SIZE_A);
            mean[1][j] = (square[1][j] / SIZE_A);
        }
        for (int j = 0; j < 3; j++)
        {
            rmsCurrents[j] = std::sqrt(mean[0][j]);
            rmsVoltages[j] = std::sqrt(mean[1][j]);
        }
        for(int i=0;i<2;i++)
        {
            for(int j=0; j<3; j++)
            {
                square[i][j] = 0;
            }
        }
    }

public:

    std::unique_ptr<SubscriptionLogger> p_current_sub;
    std::unique_ptr<SubscriptionLogger> p_voltage_sub;

    float rmsCurrents[3] = {0.0};
    float rmsVoltages[3] = {0.0};
    float phasePowerElectrical[3];
    float totalPowerElectrical;
    float phasePowerReactive[3];
    float totalPowerReactive;
    bool vReady = false;
    bool cReady = false;


    PowerCalculator()
    {
        currents.resize(3);
        voltages.resize(3);

        p_current_sub.reset(new SubscriptionLogger("/input_current"));
        p_voltage_sub.reset(new SubscriptionLogger("/input_voltage"));

    }

    void currentCallback(const tb_digital_twin::Current::ConstPtr& msg)
    {
        inputCurrent[0] = msg->current1;
        inputCurrent[1] = msg->current2;
        inputCurrent[2] = msg->current3;
        if(msg->id == p_current_sub->next_id)
        {
            p_current_sub->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_current_sub->time_diffs.push_back(diff.toNSec());
        }
        p_current_sub->next_id = msg->id + 1;

        if(c >= SIZE_A )
        {
            currentBuffer = currents;
            cReady = true;
            currents.clear();
            currents.resize(3);
            c = 0;
        }

        currents.at(0).push_back(msg->current1);
        currents.at(1).push_back(msg->current2);
        currents.at(2).push_back(msg->current3);

        c++;
    }
    void voltageCallback(const tb_digital_twin::Voltage::ConstPtr& msg)
    {
        inputVoltage[0] = msg->voltage1;
        inputVoltage[1] = msg->voltage2;
        inputVoltage[2] = msg->voltage3;
        if(msg->id == p_voltage_sub->next_id)
        {   p_voltage_sub->recv_counter += 1;
            ros::Duration diff = ros::Time::now() - msg->stamp;
            p_voltage_sub->time_diffs.push_back(diff.toNSec());
        }
        p_voltage_sub->next_id = msg->id + 1;
        if(v >= SIZE_A )
        {
            voltageBuffer = voltages;
            vReady = true;
            voltages.clear();
            voltages.resize(3);
            v = 0;
        }

        voltages.at(0).push_back(msg->voltage1);
        voltages.at(1).push_back(msg->voltage2);
        voltages.at(2).push_back(msg->voltage3);

        v++;
    }
    void calculatePowerReactive()
    {
        for(int i=0;i<3;i++)
        {
            phasePowerReactive[i] = (abs(inputCurrent[i]*inputVoltage[i]))/3;
        }
        totalPowerReactive = phasePowerReactive[0]+phasePowerReactive[1]+phasePowerReactive[2];
        //return totalPower;
    }
    bool calculatePowerElectrical()
    {
        /* BOOL to confirm calculation and not send bullcrap?*/
        if(cReady && vReady)
        {
            calculateRMS();
            phasePowerElectrical[0] = rmsCurrents[0] * rmsVoltages[0] * cosPhi;
            phasePowerElectrical[1] = rmsCurrents[1] * rmsVoltages[1] * cosPhi;
            phasePowerElectrical[2] = rmsCurrents[2] * rmsVoltages[2] * cosPhi;
            totalPowerElectrical = phasePowerElectrical[0] + phasePowerElectrical[1] + phasePowerElectrical[2];
            return true;
        }
        else
        {
            return false;
        }
    }
    void clearBuffers()
    {
        currentBuffer.clear();
        voltageBuffer.clear();
    }
    bool getCanCalculate()
    {
        return canCalculate;
    }
    void setCanCalculate(bool val)
    {
        canCalculate = val;
    }
    void setCurrentReady(bool val)
    {
        cReady = val;
    }
    void setVoltageReady(bool val)
    {
        vReady = val;
    }

};

int main(int argc, char *argv[])
{
    PowerCalculator power;
    ros::init(argc, argv, "power_calculator",ros::init_options::AnonymousName);
    ROS_DEBUG("Power Node initialized");
    ros::NodeHandle handler;
    ros::Publisher PowerReactivePublisher = handler.advertise<tb_digital_twin::Power>("motor_power/reactive_power", 100);
    ros::Publisher PowerElectricalPublisher = handler.advertise<tb_digital_twin::Power>("motor_power/electrical_power", 100);
    ros::Subscriber voltageSubscriber = handler.subscribe<tb_digital_twin::Voltage>("input_voltage", 100, &PowerCalculator::voltageCallback, &power);
    ros::Subscriber currentSubscriber = handler.subscribe<tb_digital_twin::Current>("input_current", 100, &PowerCalculator::currentCallback, &power);

    std::unique_ptr<PublisherLogger> p_electrical_power_pub;
    std::unique_ptr<PublisherLogger> p_reactive_power_pub;
    p_electrical_power_pub.reset(new PublisherLogger("/motor_power/electrical_power"));
    p_reactive_power_pub.reset(new PublisherLogger("/motor_power/reactive_power"));

    ros::Rate rate(60);

    tb_digital_twin::Power powerReactMsg;
    tb_digital_twin::Power powerElMsg;
    powerReactMsg.id = 0;
    powerElMsg.id = 0;

    while(ros::ok())
    {
        ros::spinOnce();
        power.calculatePowerReactive();
        if(power.vReady && power.cReady)
        {
            if(power.calculatePowerElectrical())
            {
                powerElMsg.phase1 = power.phasePowerElectrical[0];
                powerElMsg.phase2 = power.phasePowerElectrical[1];
                powerElMsg.phase3 = power.phasePowerElectrical[2];
                powerElMsg.total = power.totalPowerElectrical;
                power.clearBuffers();
                PowerElectricalPublisher.publish(powerElMsg);
                powerElMsg.id += 1;
                p_electrical_power_pub->sent_counter +=1;

                power.setCurrentReady(false);
                power.setVoltageReady(false);
                power.setCanCalculate(false);
            }
        }
        powerReactMsg.phase1 = power.phasePowerReactive[0];
        powerReactMsg.phase2 = power.phasePowerReactive[1];
        powerReactMsg.phase3 = power.phasePowerReactive[2];
        powerReactMsg.total = power.totalPowerReactive;
        PowerReactivePublisher.publish(powerReactMsg);
        powerReactMsg.id += 1;
        p_reactive_power_pub->sent_counter += 1;
        rate.sleep();
    }
    DataLogger::save_logged_data("power_calculator.csv");
    return 0;
}