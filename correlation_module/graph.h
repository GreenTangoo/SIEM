#ifndef GRAPH_H
#define GRAPH_H

#include "sub_graph.h"
#include "recognition_interface.hpp"
#include "correlation_module/all_symptoms.hpp"

namespace topology_space
{
    class Graph
    {
    private:
        std::list<SubGraph> allSubGraphs;
        recognition_space::RecognitionInter* initializedVec; // Contains symptoms group by APT Mitre Matrix groups
    private:
        std::vector<symptoms_space::SymptomImpl*> initializeAccountAccessSymptoms();
        std::vector<symptoms_space::SymptomImpl*> initializeDiscoveredSymptoms();
        std::vector<symptoms_space::SymptomImpl*> initializeFilesManipulationSymptoms();
        std::vector<symptoms_space::SymptomImpl*> initializeProccessManipulationSymptoms();
        void crop_unsuspicious_sub_graphs();
    public:
        Graph();
        ~Graph();
        void initializeRecognitionMethods();
        void fillGraph(); // Constructs sub_graph objects and add them to all_sub_graphs object
        std::list<SubGraph> getAllSubGraphs();
    };
}
#endif // GRAPH_H
