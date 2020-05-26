#ifndef APACHE_AGGR_HPP
#define APACHE_AGGR_HPP

#include "../aggregator_interface/aggr_interface_implementation.hpp"
#include "../../time_class/parse_time.hpp"

namespace aggregator_space
{
    class ApacheAggregator : public AggregatorImpl
    {
    private:
        std::string resultJsonFilename;
    private:
        std::string convertApacheDateFormat(std::string apacheDate);
    public:
        ApacheAggregator(const std::string &logFilename, const std::string &resultJsonFilename);
        ApacheAggregator(const ApacheAggregator &other);
        ApacheAggregator(ApacheAggregator &&other) = delete;
        virtual ~ApacheAggregator();
        virtual void getInformationFromLogs();
    };
}

#endif // APACHE_AGGR_HPP
