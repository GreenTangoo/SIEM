#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP

#include "../aggregator/parser_json/json.hpp"
#include "../correlation_module/sub_graph.h"

namespace analysis
{
    class prediction
    {
    private:
        std::vector<std::pair<std::string, std::vector<std::string>>> file_get_symptoms;
        std::vector<std::pair<std::string, std::vector<std::string>>> prediction_symptoms;
    private:
        void fillSymptomsName();
    public:
        prediction();
        prediction(const topology::sub_graph &sub_graph_obj);
        ~prediction();
        void analyseSubGraph(const topology::sub_graph &sub_graph_obj);
        std::vector<std::pair<std::string, std::vector<std::string>>> getPredictionSymptoms() const;
    };
}

#endif
