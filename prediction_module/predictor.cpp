#include "predictor.hpp"

analysis::prediction::prediction()
{
    fillSymptomsName();
}

analysis::prediction::prediction(const topology_space::SubGraph &sub_graph_obj)
{
    fillSymptomsName();
    analyseSubGraph(sub_graph_obj);
}

analysis::prediction::~prediction()
{

}
/*This method compares symptoms gots from file and recgonized symptoms*/
void analysis::prediction::analyseSubGraph(const topology_space::SubGraph &sub_graph_obj)
{
    prediction_symptoms.clear();
    std::vector<topology_space::SymptomInfo> symp_info = sub_graph_obj.getSymptomInfo();
    std::vector<std::string> getted_info;

    /*Gets category type symptoms from sub_graphs*/
    for(size_t i(0); i < symp_info.size(); i++)
        getted_info.push_back(category_space::CategoryResolver::getInstance().getCategoryName(symp_info[i].sympType));
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
    json_space::JsonObject parser = getJsonData("vector_attacks.json");

    std::shared_ptr<JsonContainer> container = parser.findElementByName("attacks");

    container = container->childNode;
    /*Moving through the attacks type vector*/
    for(; container != nullptr; container = container->nextNode)
    {
        std::vector<std::string> arr_symp;
        std::shared_ptr<JsonContainer> container_array_symp = container->childNode->childNode;
        /*Moving through the symptoms of attack vector(like APT1)*/
        for(; container_array_symp != nullptr; container_array_symp = container_array_symp->nextNode)
            arr_symp.push_back(container_array_symp->keyValue.second);

        std::sort(arr_symp.begin(), arr_symp.end());
        std::pair<std::string, std::vector<std::string>> one_theory_vector = std::make_pair(container->keyValue.first, arr_symp);

        file_get_symptoms.push_back(one_theory_vector);
    }
}
