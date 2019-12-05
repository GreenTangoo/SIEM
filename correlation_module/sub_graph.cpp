#include "sub_graph.h"

using namespace topology;

sub_graph::sub_graph()
{

}

sub_graph::sub_graph(std::vector<std::pair<std::string, int16_t>> info, category::symptom_category symp_categrory, data_time::time time)
{
    topology::symptom_info obj;
    obj.info = info;
    obj.symp_type = symp_categrory;
    obj.time = time;

    signs_vec.push_back(obj);
}

sub_graph::~sub_graph()
{

}

const std::vector<symptom_info> sub_graph::getSymptomInfo() const
{
    return signs_vec;
}

void sub_graph::addSymptomInfo(symptoms::Symptom_impl *symp)
{
    for(size_t i(0); i < symp->getData().size(); i++)
    {
        for(size_t j(0); j < this->signs_vec.size(); j++)
        {
            std::vector<std::pair<std::string, int16_t>> out_vec;
            /*try {
            std::sort(symp->getData()[i].main_data.begin(), symp->getData()[i].main_data.end(),
                      [](std::pair<std::string, int16_t> first_elem, std::pair<std::string, int16_t> second_elem) -> bool
            {
               return first_elem.first > second_elem.first;
            });

            std::sort(this->signs_vec[j].info.begin(), this->signs_vec[j].info.end(),
                      [](std::pair<std::string, int16_t> first_elem, std::pair<std::string, int16_t> second_elem) -> bool
            {
               return first_elem.first > second_elem.first;
            });
            }catch(...) {std::cout << "Except" << std::endl; abort();}*/
            std::set_intersection(symp->getData()[i].main_data.begin(), symp->getData()[i].main_data.end(),
                    this->signs_vec[j].info.begin(), this->signs_vec[j].info.end(), std::back_inserter(out_vec),
                      [](std::pair<std::string, int16_t> first_elem, std::pair<std::string, int16_t> second_elem) -> bool
            {
                if((first_elem.first == second_elem.first) && (first_elem.second > 0))
                    return true;
                else return false;
            });

            if(out_vec.size() > 0)
            {
                topology::symptom_info obj;
                obj.info = symp->getData()[i].main_data;
                obj.symp_type = symp->getSymptomType();
                obj.time = symp->getData()[i].time;

                signs_vec.push_back(obj);
            }
        }
    }
}
