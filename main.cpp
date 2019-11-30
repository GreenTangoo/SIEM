#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"
#include "prediction_module/predictor.hpp"

using namespace topology;

int main()
{
    topology::graph graph_obj;
    graph_obj.initializeRecognitionMethods();
    graph_obj.fillGraph();

    std::list<sub_graph> return_vec = graph_obj.getAllSubGraphs();

    for(std::list<sub_graph>::iterator it = return_vec.begin(); it != return_vec.end(); it++)
    {
        std::cout << "Sub graph" << std::endl;
        analysis::prediction predictor_obj(*it);
        std::vector<std::string> later_types_attacks = predictor_obj.getProbablyLaterSymptoms();
        if(later_types_attacks.size() > 0)
            for(size_t i(0); i < later_types_attacks.size(); i++)
                std::cout << "Probably next attack: " << later_types_attacks[i] << std::endl;

        std::vector<symptom_info> info = it->getSymptomInfo();
        for(size_t j(0); j < info.size(); j++)
        {
            std::cout << "One symptom" << std::endl;
            for(size_t k(0); k < info[j].vec_info.size(); k++)
            {
                std::cout << "    -" << info[j].vec_info[k] << std::endl;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
