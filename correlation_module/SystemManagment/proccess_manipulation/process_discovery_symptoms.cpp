#include "process_discovery_symptoms.hpp"

using namespace symptoms::proccess_manipulation;


ProcessDiscoverySymptoms::ProcessDiscoverySymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::process_discovery;
}

ProcessDiscoverySymptoms::~ProcessDiscoverySymptoms()
{

}

bool ProcessDiscoverySymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("users");
    container = container->down;
    if(container->cell_type == jsoner::NONE)
        return false;
    for(; container->down != nullptr; container->down = container->down->next)
    {
        if((container->down->one_cell.first == "ps") &&
                (container->down->down->next->one_cell.second == "start"))
        {
            symptoms::data data_obj;
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->one_cell.first, 1)); // Get name
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->one_cell.first, 0)); // Get process name
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->down->next->one_cell.first +
                                                ":" + container->down->down->next->one_cell.second, 0)); // Get action
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->down->next->next->one_cell.first +
                                                ":" + container->down->down->next->next->one_cell.second, 0)); // Get privilieges
            data_obj.time = data_time::time(container->down->down->one_cell.second);
            data_obj.is_used = false;
            this->all_data_from_symptom.push_back(data_obj);
        }
    }

    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
