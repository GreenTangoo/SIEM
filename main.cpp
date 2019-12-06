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

int main()
{
    /*topology::graph graph_obj;
    graph_obj.initializeRecognitionMethods();
    graph_obj.fillGraph();

    std::list<sub_graph> return_vec = graph_obj.getAllSubGraphs();

    for(std::list<sub_graph>::iterator it = return_vec.begin(); it != return_vec.end(); it++)
    {
        std::cout << "One sub graph" << std::endl;
        std::vector<symptom_info> symptoms = it->getSymptomInfo();

        for(size_t i(0); i < symptoms.size(); i++)
        {
            std::cout << "One symptom" << std::endl;
            std::cout << "Time: " << symptoms[i].time.getStrTime() << std::endl;
            std::cout << "Category: " << category::getCategoryName(symptoms[i].symp_type) << std::endl;

            for(size_t j(0); j < symptoms[i].info.size(); j++)
                std::cout << "Information: " << symptoms[i].info[j].first << std::endl;
        }
    }*/

    std::vector<std::pair<int, char>> obj1 = {std::pair<int,char>(1,'a'), std::pair<int,char>(2,'c'), std::pair<int,char>(3,'c'),
                                             std::pair<int,char>(4,'b')};
    std::vector<std::pair<int, char>> obj2 = {std::pair<int,char>(1,'d'), std::pair<int,char>(2,'i'), std::pair<int,char>(3,'x'),
                                             std::pair<int,char>(5,'b')};

    std::vector<std::pair<int,char>> result;

    std::set_intersection(obj1.begin(), obj1.end(), obj2.begin(), obj2.end(), std::back_inserter(result),
                          [](std::pair<int,char> one, std::pair<int,char> two) -> bool
    {
        if(one.first == two.first)
            return false;
        else return true;
    });

    for(size_t i(0); i < result.size(); i++)
        std::cout << result[i].first << " " << result[i].second << std::endl;
    return 0;
}
