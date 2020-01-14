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
/*This method compares symptoms gots from file and recgonized symptoms*/
void analysis::prediction::analyseSubGraph(const topology::sub_graph &sub_graph_obj)
{
    prediction_symptoms.clear();
    std::vector<topology::symptom_info> symp_info = sub_graph_obj.getSymptomInfo();
    std::vector<std::string> getted_info;

    /*Gets category type symptoms from sub_graphs*/
    for(size_t i(0); i < symp_info.size(); i++)
        getted_info.push_back(category::category_resolver::getInstance().getCategoryName(symp_info[i].symp_type));
    std::sort(getted_info.begin(), getted_info.end());

    /*Moving through the symptoms was got from file*/
    for(size_t i(0); i < file_get_symptoms.size(); i++)
    {
        std::vector<std::string> out_vec;
        /*Finding the consilience*/
        std::set_intersection(file_get_symptoms[i].second.begin(), file_get_symptoms[i].second.end(),
                              getted_info.begin(), getted_info.end(), std::back_inserter(out_vec));
        /*If founded 30% of consilience*/
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

/*This method gets attack vectors names and it symptoms from json file*/
void analysis::prediction::fillSymptomsName()
{
    jsoner::json_parser parser = jsoner::getJsonData("vector_attacks.json");

    jsoner::json_container *container = parser.find_element_by_name("attacks");

    container = container->down;
    /*Moving through the attacks type vector*/
    for(; container != nullptr; container = container->next)
    {
        std::vector<std::string> arr_symp;
        jsoner::json_container *container_array_symp = container->down->down;
        /*Moving through the symptoms of attack vector(like APT1)*/
        for(; container_array_symp != nullptr; container_array_symp = container_array_symp->next)
            arr_symp.push_back(container_array_symp->one_cell.second);

        std::sort(arr_symp.begin(), arr_symp.end());
        std::pair<std::string, std::vector<std::string>> one_theory_vector = std::make_pair(container->one_cell.first, arr_symp);

        file_get_symptoms.push_back(one_theory_vector);
    }
}
