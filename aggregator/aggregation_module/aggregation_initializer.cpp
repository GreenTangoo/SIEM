#include "aggregation_initializer.hpp"
#include "../../logfile_defines.hpp"

using namespace aggregator_space;
using namespace aggregator_init_space;

AggregationsContainer::AggregationsContainer()
{

}

AggregationsContainer::AggregationsContainer(AggregatorImpl *obj)
{
    allAggreagations.push_back(obj);
}

AggregationsContainer::AggregationsContainer(std::vector<AggregatorImpl*> vectorObj)
{
    allAggreagations = vectorObj;
}

AggregationsContainer::~AggregationsContainer()
{
    for(size_t i(0); i < allAggreagations.size(); i++)
        delete allAggreagations[i];
}

void AggregationsContainer::addAggregator(AggregatorImpl *obj)
{
    allAggreagations.push_back(obj);
}

void AggregationsContainer::addAggregator(std::vector<AggregatorImpl*> vectorObj)
{
    allAggreagations.insert(allAggreagations.end(), vectorObj.begin(), vectorObj.end());
}

void AggregationsContainer::aggregateInformation()
{
    for(size_t i(0); i < allAggreagations.size(); i++)
    {
        allAggreagations[i]->getInformationFromLogs();
    }
}

//---------------------------------AGGREGATIONINITIALIZER--------------------------------------

AggregationInitializer::AggregationInitializer()
{
    aggrContainer.addAggregator(initializeApacheAggregation());
    aggrContainer.addAggregator(initializeIptablesAggregation());
    aggrContainer.addAggregator(initializeSystemAuthAggregation());
}

void AggregationInitializer::startAggregation()
{
    aggrContainer.aggregateInformation();
}

std::vector<AggregatorImpl*> AggregationInitializer::initializeApacheAggregation()
{
    std::vector<AggregatorImpl*> apacheAggregators;

    ApacheAggregator *apacheAggr = new ApacheAggregator(APACHE_SOURCE_LOG_PATH, APACHE_LOG_PATH);

    apacheAggregators.push_back(apacheAggr);
    return apacheAggregators;
}

std::vector<AggregatorImpl*> AggregationInitializer::initializeIptablesAggregation()
{
    std::vector<AggregatorImpl*> iptablesAggregators;

    IptablesAggregator *iptablesAggr = new IptablesAggregator(IPTABLES_SOURCE_LOG_PATH, IPTABLES_LOG_PATH);

    iptablesAggregators.push_back(iptablesAggr);
    return iptablesAggregators;
}

std::vector<AggregatorImpl*> AggregationInitializer::initializeSystemAuthAggregation()
{
    std::vector<AggregatorImpl*> systemAuthAggregators;

    SystemAuthAggregator *systemAuthAggr = new SystemAuthAggregator(SYSTEM_AUTHORIZATION_SOURCE_LOG_PATH, SYSTEM_AUTHORIZATION_LOG_PATH);

    systemAuthAggregators.push_back(systemAuthAggr);
    return systemAuthAggregators;
}
