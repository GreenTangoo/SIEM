#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"
#include "prediction_module/predictor.hpp"
#include "aggregator/time_class/parse_time.hpp"

using namespace topology;

void displayPrediction(const analysis::prediction &obj, std::ofstream &fout)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> returned_pred = obj.getPredictionSymptoms();

    for(size_t i(0); i < returned_pred.size(); i++)
    {
        std::cout << "Attack vector name: " << returned_pred[i].first << "\n";
        for(size_t j(0); j < returned_pred[i].second.size(); j++)
            std::cout << "    Possible later symptoms: " << returned_pred[i].second[j] << "\n";
    }
}

int get_interger(const char *msg)
{
    int n;
    char answer[256];

    fgets(answer, sizeof(answer), stdin);

    while(sscanf(answer, "%d", &n) != 1)
    {
        fflush(stdin);
        fgets(answer, sizeof(answer), stdin);
    }

    return n;
}

int main()
{
    /*std::ofstream fout;
    fout.open("result.txt", std::ios_base::out);
    if(fout.is_open() == false)
        return -1;



    topology::graph graph_obj;
    graph_obj.initializeRecognitionMethods();
    graph_obj.fillGraph();

    std::list<sub_graph> return_vec = graph_obj.getAllSubGraphs();

    for(std::list<sub_graph>::iterator it = return_vec.begin(); it != return_vec.end(); it++)
    {
        analysis::prediction prediction_obj(*it);
        displayPrediction(prediction_obj, fout);

        std::cout << "One sub graph" << "\n";
        std::vector<symptom_info> symptoms = it->getSymptomInfo();

        for(size_t i(0); i < symptoms.size(); i++)
        {
            std::cout << "  One symptom" << "\n";
            std::cout << "      Time: " << symptoms[i].time.getStrTime() << "\n";
            std::cout << "      Category: " << category::category_resolver::getInstance().getCategoryName(symptoms[i].symp_type) << "\n";

            for(size_t j(0); j < symptoms[i].info.size(); j++)
                std::cout << "      Information: " << symptoms[i].info[j].first << "\n";
        }
        std::cout << "\n";
    }*/

    std::cout << get_interger("") << std::endl;

    return 0;
}
