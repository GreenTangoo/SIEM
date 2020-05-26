#ifndef AGGR_INTERFACE_IMPLEMENTATION_HPP
#define AGGR_INTERFACE_IMPLEMENTATION_HPP

#include <string>
#include <fstream>

#include "main_aggr_interface.hpp"

namespace aggregator_space
{
    class AggregatorImpl : public AggregatorInterface
    {
    protected:
        std::string logFileFilename;
        json_space::JsonObject jsonLogRepresentation;
    public:
        AggregatorImpl();
        AggregatorImpl(const AggregatorImpl &other);
        AggregatorImpl(AggregatorImpl &&other) = delete;
        virtual ~AggregatorImpl();
        virtual void getInformationFromLogs() = 0;

    };
}

#endif // AGGR_INTERFACE_IMPLEMENTATION_HPP
