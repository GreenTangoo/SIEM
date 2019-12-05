#include "user_login_symptoms.hpp"

using namespace symptoms::account_access;


UserLoginSymptoms::UserLoginSymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::user_login;
}

UserLoginSymptoms::~UserLoginSymptoms()
{

}

bool UserLoginSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);
    jsoner::json_container *container = parser.find_element_by_name("users");
    container = container->down;

    for(; container != nullptr; container = container->next)
    {
        symptoms::data data_obj;
        data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->one_cell.first, 1)); // Get username
        data_obj.main_data.push_back(std::pair<std::string, int16_t>(container->down->next->one_cell.second, 1)); // Get ip
        data_obj.time = data_time::time(container->down->one_cell.second);
        this->all_data_from_symptom.push_back(data_obj);
    }
    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
