#include "all_categories.hpp"

using namespace category;

category_resolver::category_resolver()
{

}

category_resolver& category_resolver::getInstance()
{
    static category_resolver instance;
    return instance;
}

std::string category_resolver::getCategoryName(symptom_category symptom_category)
{
    if(symptom_category == user_login)
        return std::string("user_login");
    if(symptom_category == login_root)
        return std::string("login_root");
    if(symptom_category == directory_discovery)
        return std::string("directory_discovery");
    if(symptom_category == port_scanning)
        return std::string("port_scanning");
    if(symptom_category == command_line_interface)
        return std::string("command_line_interface");
    if(symptom_category == account_discovery)
        return std::string("account_discovery");
    if(symptom_category == process_discovery)
        return std::string("process_discovery");
    if(symptom_category == system_network_configuration_discovery)
        return std::string("system_network_configuration_discovery");
    if(symptom_category == system_network_connection_discovery)
        return std::string("system_network_connection_discovery");
    if(symptom_category == data_collection)
        return std::string("data_collection");
    if(symptom_category == data_compressed)
        return std::string("data_compressed");
}
