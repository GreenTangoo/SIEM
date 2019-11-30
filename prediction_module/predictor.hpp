#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP

#include <fstream>

#include "../aggregator/parser_txt/parser.hpp"
#include "../correlation_module/sub_graph.h"

namespace analysis
{
    class prediction
    {
    private:
        std::vector<std::string> probably_later_categories;
    public:
        prediction();
        prediction(const topology::sub_graph &sub_graph_obj);
        ~prediction();
        void analyseSubGraph(const topology::sub_graph &sub_graph_obj);
        std::vector<std::string> getProbablyLaterSymptoms();
    };
}

#endif
