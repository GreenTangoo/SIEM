#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <ctime>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"
#include "prediction_module/predictor.hpp"
#include "aggregator/parser_json/json.hpp"
#include "aggregator/aggregation_module/aggregation_initializer.hpp"
#include "logfile_defines.hpp"

using namespace topology_space;
using namespace aggregator_init_space;

void displayPrediction(const analysis::prediction &obj, std::ostream &out)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> returnedPred = obj.getPredictionSymptoms();

    for(size_t i(0); i < returnedPred.size(); i++)
    {
        out << "Attack vector name: " << returnedPred[i].first << "\n";
        for(size_t j(0); j < returnedPred[i].second.size(); j++)
            out << "    Possible later symptoms: " << returnedPred[i].second[j] << "\n";
    }
}

int main(int argc, char **argv)
{
    long startTime = clock();

    try
    {
        std::ofstream fout;
        fout.open("result.txt", std::ios_base::out);
        if(fout.is_open() == false)
            return -1;


        AggregationInitializer initAggregationObject;
        initAggregationObject.startAggregation();

        topology_space::Graph graphObj;
        graphObj.initializeRecognitionMethods();
        graphObj.fillGraph();

        std::list<SubGraph> returnVec = graphObj.getAllSubGraphs();

        for(std::list<SubGraph>::iterator it = returnVec.begin(); it != returnVec.end(); it++)
        {
            analysis::prediction prediction_obj(*it);
            displayPrediction(prediction_obj, fout);

            fout << "One sub graph" << "\n";
            std::vector<SymptomInfo> symptoms = it->getSymptomInfo();

            for(size_t i(0); i < symptoms.size(); i++)
            {
                fout << "  One symptom" << "\n";
                fout << "      Time: " << symptoms[i].time.getStrTime() << "\n";
                fout << "      Category: " << category_space::CategoryResolver::getInstance().getCategoryName(symptoms[i].sympType) << "\n";

                for(size_t j(0); j < symptoms[i].info.size(); j++)
                    fout << "      Information: " << symptoms[i].info[j].first << "\n";
            }
            fout << "\n";
        }
    }
    catch(const SIEM_errors::SIEMException &ex)
    {
        std::cout << "Exception catched: " << ex.what() << std::endl;
    }

    long endTime = clock();

    std::cout << (endTime - startTime) / 1000.0 << std::endl;

    return 0;
}

