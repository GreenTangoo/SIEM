#ifndef GRAPH_H
#define GRAPH_H

#include "sub_graph.h"
#include "recognition_interface.hpp"
#include "correlation_module/all_symptoms.hpp"

namespace topology
{
    class graph
    {
    private:
        std::vector<sub_graph> all_sub_graphs;
        std::vector<recognition::recognition_inter*> initialized_vec;
    private:
        std::vector<symptoms::Symptom*> initializeAccountAccessSymptoms();
        std::vector<symptoms::Symptom*> initializeDiscoveredSymptoms();
        void getOneAttackVector(size_t curr_index, sub_graph &obj);
    public:
        graph();
        ~graph();
        void initializeRecognitionMethods();
        void fillGraph();
        std::vector<sub_graph> getAllSubGraphs();
    };
}
#endif // GRAPH_H
