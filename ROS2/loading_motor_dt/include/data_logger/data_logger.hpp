//  This file contains the Data Logger library definitions and declarations
//  used in ROS and ROS2 latency evaluation study.
//  Last modified: 05.11.2021
//  source: https://github.com/TalTech-PSG453/ros_ros2_latency_evaluation

#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include <iostream> // header in standard library
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>

/* 
    DataLogger is an umbrella for 2 classes: SubscriptionLogger and PublisherLogger
    These classes are used inside the ROS nodes for corresponding topics of the node
    (either for publishing or for subscription)
*/
namespace DataLogger
{

    // The subscription logger takes care of topics used for subscription in a particular node.

    class SubscriptionLogger
    {
       
        public:

        SubscriptionLogger(std::string topic_name);
        ~SubscriptionLogger();

        /*variables*/
        std::string topic;
        std::vector<uint32_t> time_diffs;
        unsigned long long recv_counter;
        unsigned long long next_id;

        uint32_t get_mean();
        uint32_t get_max_latency();
        uint32_t get_min_latency();

        static std::vector<SubscriptionLogger*> get_list_of_loggers();
        
        private:

        // This can be a troublesome declaration, with potential for memory leaks...
        static std::vector<SubscriptionLogger*> loggerList;
    };

    class PublisherLogger
    {
        public:
        
        PublisherLogger(std::string topic_name);
        ~PublisherLogger();

        /* variables */
        unsigned long long sent_counter;
        std::string topic;


        static std::vector<PublisherLogger*> get_list_of_loggers();
        
        private:
        
        /* This is bad and must be fixed later... I just don't know how to make it with smart pointers without causing memory leaks, therefore
        this is temporary fix, simpler but hopefully it won't break anything*/
        static std::vector<PublisherLogger*> loggerList;
    };

    void save_logged_data(std::string filename);
}
#endif