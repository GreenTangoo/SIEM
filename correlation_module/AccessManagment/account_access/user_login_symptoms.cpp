#include "user_login_symptoms.hpp"

using namespace symptoms::account_access;


UserLoginSymptoms::UserLoginSymptoms(std::string filename) : json_filename(filename)
{
}

UserLoginSymptoms::~UserLoginSymptoms()
{

}

bool UserLoginSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("auth_log");
    container = container->down;
    for(; container != nullptr; container = container->next)
    {
        if(container->one_cell.second == "Login")
            return true;
    }
    return false;
}

std::string UserLoginSymptoms::warning_msg()
{
    return "Warning: user login in system";
}
