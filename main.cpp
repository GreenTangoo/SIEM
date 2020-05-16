#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"
#include "correlation_module/CustomCorrelation/config_descriptor.hpp"
#include "prediction_module/predictor.hpp"
#include "aggregator/time_class/parse_time.hpp"

#include "aggregator/parser_json/json.hpp"

using namespace topology_space;

void displayPrediction(const analysis::prediction &obj, std::ofstream &fout)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> returnedPred = obj.getPredictionSymptoms();

    for(size_t i(0); i < returnedPred.size(); i++)
    {
        fout << "Attack vector name: " << returnedPred[i].first << "\n";
        for(size_t j(0); j < returnedPred[i].second.size(); j++)
            fout << "    Possible later symptoms: " << returnedPred[i].second[j] << "\n";
    }
}

int main(int argc, char **argv)
{
    try
    {
        std::ofstream fout;
        fout.open("result.txt", std::ios_base::out);
        if(fout.is_open() == false)
            return -1;



        topology_space::Graph graphObj;
        graphObj.initializeRecognitionMethods();
        graphObj.fillGraph();

        std::list<SubGraph> returnVec = graphObj.getAllSubGraphs();

        for(std::list<SubGraph>::iterator it = returnVec.begin(); it != returnVec.end(); it++)
        {
            analysis::prediction prediction_obj(*it);
            //displayPrediction(prediction_obj, fout);

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


    /*jsoner_space::JsonParser parser = getJsonData("auth.json");
    std::list<jsoner_space::JsonContainer*> listContainter = parser.findElementsByName("users");

    std::cout << listContainter.size() << std::endl;
    std::cout << "Hello world"  << std::endl;*/

    /*symptoms_space::DescriptorConfig obj;
    std::vector<symptoms_space::OneConfigCell> vecDesc = obj.getDescription("corr.json");
    std::cout << "" << std::endl;*/
    return 0;
}

