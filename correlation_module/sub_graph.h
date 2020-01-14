#ifndef SUB_GRAPH_H
#define SUB_GRAPH_H

#include <list>
#include <vector>
#include <string>

#include "recognition_interface.hpp"

namespace topology
{
    /*symptom_info contains all information about one symptom*/
    struct symptom_info
    {
        std::vector<std::pair<std::string, int16_t>> info;
        category::symptom_category symp_type;
        data_time::time time;
    };
    /*One sub_graph object contains the sequence of probably relative symptoms*/
    class sub_graph
    {
    private:
        std::vector<symptom_info> signs_vec;
    public:
        sub_graph();
        sub_graph(std::vector<std::pair<std::string, int16_t>> info, category::symptom_category symp_categrory, data_time::time time);
        ~sub_graph();
        const std::vector<symptom_info> getSymptomInfo() const;
        void addSymptomInfo(symptoms::Symptom_impl *symp);
    };
}
#endif // SUB_GRAPH_H
