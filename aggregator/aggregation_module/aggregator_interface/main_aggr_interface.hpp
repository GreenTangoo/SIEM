#ifndef MAIN_AGGR_INTERFACE_HPP
#define MAIN_AGGR_INTERFACE_HPP

#include "../../parser_json/json.hpp"
#include "../../parser_txt/parser.hpp"

namespace aggregator_space
{
    class AggregatorInterface
    {
    public:
        AggregatorInterface() = default;
        AggregatorInterface(const AggregatorInterface &other) = default;
        AggregatorInterface(AggregatorInterface &&other) = delete;
        virtual ~AggregatorInterface() = default;
        virtual void getInformationFromLogs() = 0;
    };
}

#endif // MAIN_AGGR_INTERFACE_HPP
