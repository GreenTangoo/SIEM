#include "sub_graph.h"

using namespace topology;

sub_graph::sub_graph()
{

}

sub_graph::~sub_graph()
{

}

std::vector<symptom_info> sub_graph::getSymptomInfo()
{
    return signs_vec;
}

void sub_graph::addSymptomInfo(std::vector<std::string> info)
{
    symptom_info obj;
    obj.vec_info = info;
    signs_vec.push_back(obj);
}
