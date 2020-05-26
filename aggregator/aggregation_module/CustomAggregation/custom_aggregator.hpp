#ifndef CUSTOM_AGGREGATOR_HPP
#define CUSTOM_AGGREGATOR_HPP

#include "../aggregator_interface/aggr_interface_implementation.hpp"
#include "../../../config_descriptor.hpp"

using namespace config_space;

namespace aggregator_space
{
    class CustomAggreagator : public AggregatorImpl
    {
    private:
        OneConfigCell jsonConfigCell;
    public:
        CustomAggreagator(const std::string &resultJsonFile);
        CustomAggreagator(const CustomAggreagator &other);
        CustomAggreagator(CustomAggreagator &&other) = delete;
        virtual ~CustomAggreagator();
        virtual void getInformationFromLogs();
    };
}

#endif // CUSTOM_AGGREGATOR_HPP
