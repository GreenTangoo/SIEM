#include "sub_graph.h"

using namespace topology;

sub_graph::sub_graph()
{

}

sub_graph::~sub_graph()
{

}

const std::vector<symptom_info> sub_graph::getSymptomInfo() const
{
    return signs_vec;
}

void sub_graph::addSymptomInfo(std::vector<std::string> info, category::symptom_category type)
{
    symptom_info obj;
    obj.vec_info = info;
    obj.symp_type = type;
    signs_vec.push_back(obj);
}
