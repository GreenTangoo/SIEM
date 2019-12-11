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
    std::vector<symptoms::data> symptom_data = symp->getData();
    for(size_t i(0); i < symptom_data.size(); i++)
    {
        std::vector<symptom_info> temp_signs_vec = this->signs_vec;

        for(size_t j(0); j < this->signs_vec.size(); j++)
        {
            std::vector<std::pair<std::string, int16_t>> out_vec;

            std::sort(symptom_data[i].main_data.begin(), symptom_data[i].main_data.end(), [](const std::pair<std::string, int16_t> &obj1, const std::pair<std::string, int16_t> &obj2)
            {
                return obj1.first < obj2.first;
            });
            std::sort(this->signs_vec[j].info.begin(), this->signs_vec[j].info.end(), [](const std::pair<std::string, int16_t> &obj1, const std::pair<std::string, int16_t> &obj2)
            {
                return obj1.first < obj2.first;
            });

            std::set_intersection(symptom_data[i].main_data.begin(), symptom_data[i].main_data.end(),
                    this->signs_vec[j].info.begin(), this->signs_vec[j].info.end(), std::back_inserter(out_vec),
                      [](std::pair<std::string, int16_t> first_elem, std::pair<std::string, int16_t> second_elem) -> bool
            {
                if(first_elem.second == 0)
                    return true;
                if(first_elem.first < second_elem.first)
                    return true;
                else return false;
            });

            if(out_vec.size() > 0)
            {
                if(symp->getData()[i].is_used == true)
                    continue;
                symp->getData()[i].is_used = true;
                topology::symptom_info obj;
                obj.info = symptom_data[i].main_data;
                obj.symp_type = symp->getSymptomType();
                obj.time = symptom_data[i].time;

                if(count_if(temp_signs_vec.begin(), temp_signs_vec.end(), [&obj](const symptom_info &sign_obj)
                {
                    return ((obj.symp_type == sign_obj.symp_type) && (obj.time == sign_obj.time));
                }) == 0)
                    temp_signs_vec.push_back(obj);
                else std::cout << category::category_resolver::getInstance().getCategoryName(obj.symp_type) << " " << obj.time.getStrTime() << std::endl;
            }
        }
        this->signs_vec = temp_signs_vec;
    }
}
