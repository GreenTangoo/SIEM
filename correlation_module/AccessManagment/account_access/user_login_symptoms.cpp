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
        symptoms::data user_data_obj;
        user_data_obj.main_data.push_back(container->one_cell.first);         // Get name user logon
        user_data_obj.main_data.push_back(container->down->one_cell.second);  // Get user ip
        this->all_data_from_symptom.push_back(user_data_obj);
    }
    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
