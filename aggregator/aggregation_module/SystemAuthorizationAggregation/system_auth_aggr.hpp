#ifndef SYSTEM_AUTH_AGGR_HPP
#define SYSTEM_AUTH_AGGR_HPP

#include <map>

#include "../aggregator_interface/aggr_interface_implementation.hpp"
#include "../../time_class/parse_time.hpp"

namespace aggregator_space
{
    class SystemAuthAggregator : public AggregatorImpl
    {
    private:
        std::string resultJsonFilename;
    private:
        std::string constructTimeString(std::list<std::string> parsedStringList);
    public:
        SystemAuthAggregator(const std::string &logFilename, const std::string &resultJsonFilename);
        SystemAuthAggregator(const SystemAuthAggregator &other);
        SystemAuthAggregator(SystemAuthAggregator &&other) = delete;
        virtual ~SystemAuthAggregator();
        virtual void getInformationFromLogs();
    };
}

#endif // SYSTEM_AUTH_AGGR_HPP
