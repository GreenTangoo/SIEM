#include "action_proccess_symptoms.hpp"

using namespace symptoms::proccess_manipulation;


ActionProccessSymptoms::ActionProccessSymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::action_proccesses;
}

ActionProccessSymptoms::~ActionProccessSymptoms()
{

}

bool ActionProccessSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("users");
    container = container->down;
    for(; container != nullptr; container = container->next)
    {
        if((container->down->down->next->one_cell.second == "start") &&
                                         (container->down->down->next->next->one_cell.second == "root"))
        {
            symptoms::data data_obj;
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->one_cell.first, 1));
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->one_cell.first, 0));
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->down->next->one_cell.first +
                                                ":" + container->down->down->next->next->one_cell.second, 0));
            data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->down->next->next->one_cell.first +
                                                ":" + container->down->down->next->next->one_cell.second, 0));
            data_obj.time = data_time::time(container->down->down->one_cell.second);
            data_obj.is_used = false;
            this->all_data_from_symptom.push_back(data_obj);
        }
    }

    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
