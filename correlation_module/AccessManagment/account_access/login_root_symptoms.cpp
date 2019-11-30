#include "login_root_symptoms.hpp"

using namespace symptoms::account_access;


LoginRootSymptoms::LoginRootSymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::login_root;
}

LoginRootSymptoms::~LoginRootSymptoms()
{

}

bool LoginRootSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);
    jsoner::json_container *container = parser.find_element_by_name("root");
    container = container->down;

    for(; container != nullptr; container = container->next)
    {
        if(container->down->one_cell.second == "denied")
        {
            symptoms::data user_data_obj;
            user_data_obj.main_data.push_back(container->one_cell.first); // Name
            user_data_obj.main_data.push_back(container->down->one_cell.second); // Result
            this->all_data_from_symptom.push_back(user_data_obj);
        }
    }

    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
