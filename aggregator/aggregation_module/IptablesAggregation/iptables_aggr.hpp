#ifndef IPTABLES_AGGR_HPP
#define IPTABLES_AGGR_HPP

#include <map>

#include "../aggregator_interface/aggr_interface_implementation.hpp"
#include "../../time_class/parse_time.hpp"

namespace aggregator_space
{
    class IptablesAggregator : public AggregatorImpl
    {
    private:
        std::string resultJsonFilename;
    public:
        IptablesAggregator(const std::string &logFilename, const std::string &resultJsonFilename);
        IptablesAggregator(const IptablesAggregator &other);
        IptablesAggregator(IptablesAggregator &&other) = delete;
        virtual ~IptablesAggregator();
        virtual void getInformationFromLogs();
    };
}

#endif // IPTABLES_AGGR_HPP
