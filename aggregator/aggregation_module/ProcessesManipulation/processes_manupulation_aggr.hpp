#ifndef PROCESSES_MANIPULATION_HPP
#define PROCESSES_MANIPULATION_HPP

#include "../aggregator_interface/aggr_interface_implementation.hpp"
#include "../../time_class/parse_time.hpp"

namespace aggregator_space
{
    class ProcManipulationAggregator : public AggregatorImpl
    {
    private:
        std::string resultJsonFilename;
        std::string username;
    public:
        ProcManipulationAggregator(const std::string &logFilename, const std::string &resultJsonFilename, const std::string &userAcc);
        ProcManipulationAggregator(const ProcManipulationAggregator &other);
        ProcManipulationAggregator(ProcManipulationAggregator &&other) = delete;
        virtual ~ProcManipulationAggregator();
        virtual void getInformationFromLogs();
    };
}

#endif // PROCESSES_MANIPULATION_HPP
