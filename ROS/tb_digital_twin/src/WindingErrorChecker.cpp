//
// Created by sejego on 22.12.20.
// TODO: Add publisher to 3D Model
//

#include <ros/ros.h>
#include <iostream>
#include <thread>
#include <cmath>
#include <tb_digital_twin/Current.h>

#include <chrono>

class WindingErrorChecker
{
public:

    std::vector<std::vector<float>> currents;
    std::vector<std::vector<float>> currentsBuff;
    bool canCalculate = false;
    bool* const pCanCalculate = &canCalculate;
    float rmsCurrents[3] = {0.0};
    float mean[3], square[3];
    float k[3];
    int i = 0;
    const int SIZE_A = 5000;

    WindingErrorChecker()
    {
        std::cout << "Init happened\n";
        currents.resize(3);
        canCalculate = false;
    }
    ~WindingErrorChecker()
    {
        currents.clear();
        currentsBuff.clear();
    }

    void currentCallback(const tb_digital_twin::Current::ConstPtr& msg)
    {
        auto start = std::chrono::system_clock::now();
        if(i >= SIZE_A )
        {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end-start;
            std::cout << "Time to get filled: " << diff.count() << std::endl;
            //std::cout << "Listened\n";
            i = 0;
            currentsBuff = currents;
            canCalculate = true;
            currents.clear();
            currents.resize(3);
        }

        currents.at(0).push_back(msg->current1);
        //std::cout<< currents[0][i] << "\n\n";
        currents.at(1).push_back(msg->current2);
        currents.at(2).push_back(msg->current3);

        i++;
    }

    void phaseChecker(bool *pNotTerminated)
    {
        //std::cout << *pCanCalculate << "\n";
        while(true)
        {
            if(!*pNotTerminated)
                break;

            if(*pCanCalculate)
            {
                //printf("Start Calculate\n");
                for(int j = 0; j<SIZE_A ; j++)
                {
                    square[0] += currentsBuff[0][j]*currentsBuff[0][j];
                    square[1] += currentsBuff[1][j]*currentsBuff[1][j];
                    square[2] += currentsBuff[2][j]*currentsBuff[2][j];
                }
                for(int j = 0; j<3;j++)
                {
                    mean[j] = (square[j] / SIZE_A);
                }
                for(int j = 0; j<3; j++)
                {
                    rmsCurrents[j] = std::sqrt(mean[j]);
                }
                for(int j = 0; j<3;j++)
                {
                    k[j] = rmsCurrents[j]/rmsCurrents[0];
                }
                for(float j : k)
                {
                    if( abs(k[0] - j) > 0.15 )
                    {
                        ROS_WARN("Potential malfunction in windings");
                    }
                }

                /* CLEANUP */
                currentsBuff.clear();
                for(float & j : square)
                {
                    j = 0;
                }
                *pCanCalculate = false;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    bool notTerminated = true;
    bool *pNotTerminated = &notTerminated;
    WindingErrorChecker wec;
    ros::init(argc, argv, "windings_checker");
    ros::NodeHandle nh;
    std::thread tPhaseChecker(&WindingErrorChecker::phaseChecker, &wec, pNotTerminated);
    ros::Subscriber currentsListener = nh.subscribe<tb_digital_twin::Current>("input_current",
                                                                              200, &WindingErrorChecker::currentCallback, &wec);
    ros::spin();
    if(!ros::ok())
    {
        notTerminated = false;
        tPhaseChecker.join();
        return 0;
    }
    return 0;
}

