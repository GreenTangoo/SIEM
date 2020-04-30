#ifndef SUB_GRAPH_H
#define SUB_GRAPH_H

#include "recognition_interface.hpp"

namespace topology_space
{
    /*symptom_info contains all information about one symptom*/
    struct SymptomInfo
    {
        std::vector<std::pair<std::string, int16_t>> info;
        category_space::symptomCategory sympType;
        data_time_space::Time time;
    };
    /*One sub_graph object contains the sequence of probably relative symptoms*/
    class SubGraph
    {
    private:
        std::vector<SymptomInfo> signsVec;
    public:
        SubGraph();
        SubGraph(std::vector<std::pair<std::string, int16_t>> info, category_space::symptomCategory sympCategrory, data_time_space::Time time);
        ~SubGraph();
        const std::vector<SymptomInfo> getSymptomInfo() const;
        void addSymptomInfo(symptoms_space::SymptomImpl *symp);
    };
}
#endif // SUB_GRAPH_H
