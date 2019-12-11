#include "predictor.hpp"

analysis::prediction::prediction()
{
    fillSymptomsName();
}

analysis::prediction::prediction(const topology::sub_graph &sub_graph_obj)
{
    fillSymptomsName();
    analyseSubGraph(sub_graph_obj);
}

analysis::prediction::~prediction()
{

}

void analysis::prediction::analyseSubGraph(const topology::sub_graph &sub_graph_obj)
{
    prediction_symptoms.clear();
    std::vector<topology::symptom_info> symp_info = sub_graph_obj.getSymptomInfo();
    std::vector<std::string> getted_info;

    for(size_t i(0); i < symp_info.size(); i++)
        getted_info.push_back(category::category_resolver::getInstance().getCategoryName(symp_info[i].symp_type));
    std::sort(getted_info.begin(), getted_info.end());

    for(size_t i(0); i < file_get_symptoms.size(); i++)
    {
        std::vector<std::string> out_vec;
        std::set_intersection(file_get_symptoms[i].second.begin(), file_get_symptoms[i].second.end(),
                              getted_info.begin(), getted_info.end(), std::back_inserter(out_vec));
        if(((double)out_vec.size() / double(getted_info.size())) > 0.3)
        {
            out_vec.clear();
            std::set_difference(file_get_symptoms[i].second.begin(), file_get_symptoms[i].second.end(),
                                getted_info.begin(), getted_info.end(), std::back_inserter(out_vec));
            prediction_symptoms.push_back(std::pair<std::string, std::vector<std::string>>(file_get_symptoms[i].first, out_vec));
        }
    }
}

std::vector<std::pair<std::string, std::vector<std::string>>> analysis::prediction::getPredictionSymptoms() const
{
    return prediction_symptoms;
}

void analysis::prediction::fillSymptomsName()
{
    jsoner::json_parser parser = jsoner::getJsonData("vector_attacks.json");

    jsoner::json_container *container = parser.find_element_by_name("attacks");

    container = container->down;
    for(; container != nullptr; container = container->next)
    {
        std::vector<std::string> arr_symp;
        jsoner::json_container *container_array_symp = container->down->down;
        for(; container_array_symp != nullptr; container_array_symp = container_array_symp->next)
            arr_symp.push_back(container_array_symp->one_cell.second);

        std::sort(arr_symp.begin(), arr_symp.end());
        std::pair<std::string, std::vector<std::string>> one_theory_vector = std::make_pair(container->one_cell.first, arr_symp);

        file_get_symptoms.push_back(one_theory_vector);
    }
}
