#ifndef GRAPH_H
#define GRAPH_H

#include "sub_graph.h"

namespace topology
{
    class graph
    {
    private:
        std::vector<sub_graph> all_binds;
    public:
        graph();
    };
}
#endif // GRAPH_H
