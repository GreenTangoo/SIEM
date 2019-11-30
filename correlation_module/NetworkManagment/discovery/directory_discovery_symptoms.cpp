#include "directory_discovery_symptoms.hpp"


using namespace symptoms::discovery;


DirectoryDiscoverySymptoms::DirectoryDiscoverySymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::directory_discovery;
}

DirectoryDiscoverySymptoms::~DirectoryDiscoverySymptoms()
{

}

bool DirectoryDiscoverySymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("requests");
    container = container->down;

    std::map<std::string, int32_t> ip_amount_req;
    for(; container != nullptr; container = container->next)
    {
        if(container->down->next->next->one_cell.second == "404")
            ip_amount_req[container->one_cell.first]++;
    }
    for(std::map<std::string, int32_t>::iterator it = ip_amount_req.begin(); it != ip_amount_req.end(); it++)
        if(it->second > 2)
        {
            symptoms::data user_data_obj;
            user_data_obj.main_data.push_back(it->first);
            this->all_data_from_symptom.push_back(user_data_obj);
        }
    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
