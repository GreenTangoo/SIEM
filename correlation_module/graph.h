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
        std::list<sub_graph> all_sub_graphs;
        std::vector<recognition::recognition_inter*> initialized_vec;
    private:
        std::vector<symptoms::Symptom_impl*> initializeAccountAccessSymptoms();
        std::vector<symptoms::Symptom_impl*> initializeDiscoveredSymptoms();
        std::vector<symptoms::Symptom_impl*> initializeFilesManipulationSymptoms();
        std::vector<symptoms::Symptom_impl*> initializeProccessManipulationSymptoms();
        void getOneAttackVector(size_t curr_index, sub_graph &obj);
        void crop_unsuspicious_sub_graphs();
    public:
        graph();
        ~graph();
        void initializeRecognitionMethods();
        void fillGraph();
        std::list<sub_graph> getAllSubGraphs();
    };
}
#endif // GRAPH_H
