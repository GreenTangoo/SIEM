#ifndef SUB_GRAPH_H
#define SUB_GRAPH_H

#include <list>
#include <vector>
#include <string>

#include "recognition_interface.hpp"

namespace topology
{
    struct symptom_info
    {
        std::vector<std::string> vec_info;
        category::symptom_category symp_type;
    };
    class sub_graph
    {
    private:
        std::vector<symptom_info> signs_vec;
    public:
        sub_graph();
        ~sub_graph();
        const std::vector<symptom_info> getSymptomInfo() const;
        void addSymptomInfo(std::vector<std::string> info, category::symptom_category type);
    };
}
#endif // SUB_GRAPH_H
