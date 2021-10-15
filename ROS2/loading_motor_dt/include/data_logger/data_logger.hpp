#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include <iostream> // header in standard library
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>

namespace DataLogger
{

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
        /*function declarations*/
        //float get_lates(float period);
        //int late;
        //int too_late;
        uint32_t get_mean();
        uint32_t get_max_latency();
        uint32_t get_min_latency();

        //void save_logged_data(std::string filename);
        static std::vector<SubscriptionLogger*> get_list_of_loggers();
        
        private:

        /* This is bad and must be fixed later... I just don't know how to make it with smart pointers without causing memory leaks, therefore
        this is temporary fix, simpler but hopefully it won't break anything*/
        static std::vector<SubscriptionLogger*> loggerList;
    };

    class PublisherLogger
    {
        public:
        
        PublisherLogger(std::string topic_name);
        ~PublisherLogger();
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