#ifndef AGGREGATION_INITIALIZER_HPP
#define AGGREGATION_INITIALIZER_HPP

#include <vector>

#include "all_aggregations.hpp"
#include "aggregator_interface/aggr_interface_implementation.hpp"

using namespace aggregator_space;

namespace aggregator_init_space
{
    class AggregationsContainer
    {
    private:
        std::vector<AggregatorImpl*> allAggreagations;
    public:
        AggregationsContainer();
        AggregationsContainer(AggregatorImpl *obj);
        AggregationsContainer(std::vector<AggregatorImpl*> vectorObj);
        ~AggregationsContainer();
        void addAggregator(AggregatorImpl *obj);
        void addAggregator(std::vector<AggregatorImpl*> vectorObj);
        void aggregateInformation();
    };

    class AggregationInitializer
    {
    private:
        AggregationsContainer aggrContainer;
    private:
        std::vector<AggregatorImpl*> initializeApacheAggregation();
        std::vector<AggregatorImpl*> initializeIptablesAggregation();
        std::vector<AggregatorImpl*> initializeSystemAuthAggregation();
    public:
        AggregationInitializer();
        void startAggregation();
    };
}

#endif // AGGREGATION_INITIALIZER_HPP
