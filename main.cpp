#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"

using namespace topology;

int main()
{
    topology::graph graph_obj;
    graph_obj.initializeRecognitionMethods();
    graph_obj.fillGraph();

    std::vector<sub_graph> return_vec = graph_obj.getAllSubGraphs();

    for(size_t i(0); i < return_vec.size(); i++)
    {
        std::cout << "Sub graph" << std::endl;
        std::vector<symptom_info> info = return_vec[i].getSymptomInfo();
        for(size_t j(0); j < info.size(); j++)
        {
            std::cout << "One symptom" << std::endl;
            for(size_t k(0); k < info[j].vec_info.size(); k++)
            {
                std::cout << info[j].vec_info[k] << std::endl;
            }
        }
    }
    return 0;
}
