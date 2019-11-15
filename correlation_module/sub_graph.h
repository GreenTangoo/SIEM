#ifndef SUB_GRAPH_H
#define SUB_GRAPH_H

#include <list>
#include <vector>
#include <string>

namespace topology
{
    class sub_graph
    {
    private:
        struct symptom_info
        {
            std::vector<std::string> vec_info;
            std::list<symptom_info*> binds;
        };
    public:
        sub_graph();
    };
}
#endif // SUB_GRAPH_H
