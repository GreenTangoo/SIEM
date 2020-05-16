#include "all_categories.hpp"

using namespace category_space;

CategoryResolver::CategoryResolver()
{

}

CategoryResolver& CategoryResolver::getInstance()
{
    static CategoryResolver instance;
    return instance;
}

/*This method returns string representation of category name*/
/*TODO: Reduce the amount of FLASH consumed */
std::string CategoryResolver::getCategoryName(symptomCategory symptomCategoryVar)
{
    if(symptomCategoryVar == user_login)
        return std::string("user_login");
    else if(symptomCategoryVar == login_root)
        return std::string("login_root");
    else if(symptomCategoryVar == directory_discovery)
        return std::string("directory_discovery");
    else if(symptomCategoryVar == port_scanning)
        return std::string("port_scanning");
    else if(symptomCategoryVar == command_line_interface)
        return std::string("command_line_interface");
    else if(symptomCategoryVar == account_discovery)
        return std::string("account_discovery");
    else if(symptomCategoryVar == process_discovery)
        return std::string("process_discovery");
    else if(symptomCategoryVar == system_network_configuration_discovery)
        return std::string("system_network_configuration_discovery");
    else if(symptomCategoryVar == system_network_connection_discovery)
        return std::string("system_network_connection_discovery");
    else if(symptomCategoryVar == data_collection)
        return std::string("data_collection");
    else if(symptomCategoryVar == data_compressed)
        return std::string("data_compressed");
    else if(symptomCategoryVar == external_remote_services)
        return std::string("external_remote_services");
    else if(symptomCategoryVar == spearphishing_attachment)
        return std::string("spearphishing_attachment");
    else if(symptomCategoryVar == supply_chain_compromise)
        return std::string("supply_chain_compromise");
    else if(symptomCategoryVar == valid_accounts)
        return std::string("valid_accounts");
    else if(symptomCategoryVar == compiled_html_file)
        return std::string("compiled_html_file");
    else if(symptomCategoryVar == exploitation_for_client_execution)
        return std::string("exploitation_for_client_execution");
    else if(symptomCategoryVar == powershell)
        return std::string("powershell");
    else if(symptomCategoryVar == scheduled_task)
        return std::string("scheduled_task");
    else if(symptomCategoryVar == windows_managment_instrumentation)
        return std::string("windows_managment_instrumentation");
    else if(symptomCategoryVar == accesebility_features)
        return std::string("accesebility_features");
    else if(symptomCategoryVar == bootkit)
        return std::string("bootkit");
    else if(symptomCategoryVar == create_account)
        return std::string("create_account");
    else if(symptomCategoryVar == modify_existing_services)
        return std::string("modify_existing_services");
    else if(symptomCategoryVar == registry_run_keys_startup_folder)
        return std::string("registry_run_keys_startup_folder");
    else if(symptomCategoryVar == process_injection)
        return std::string("process_injection");
    else if(symptomCategoryVar == code_signing)
        return std::string("code_signing");
    else if(symptomCategoryVar == connection_proxy)
        return std::string("connection_proxy");
    else if(symptomCategoryVar == dll_side_loading)
        return std::string("dll_side_loading");
    else if(symptomCategoryVar == file_deletion)
        return std::string("file_deletion");
    else if(symptomCategoryVar == indicator_removal_on_host)
        return std::string("indicator_removal_on_host");
    else if(symptomCategoryVar == masquerading)
        return std::string("masquerading");
    else if(symptomCategoryVar == modify_registry)
        return std::string("modify_registry");
    else if(symptomCategoryVar == rootkit)
        return std::string("rootkit");
    else if(symptomCategoryVar == web_service)
        return std::string("web_service");
    else if(symptomCategoryVar == credential_dumping)
        return std::string("credential_dumping");
    else if(symptomCategoryVar == input_capture)
        return std::string("input_capture");
    else if(symptomCategoryVar == network_share_discovery)
        return std::string("network_share_discovery");
    else if(symptomCategoryVar == network_service_scanning)
        return std::string("network_service_scanning");
    else if(symptomCategoryVar == system_owner_user_discovery)
        return std::string("system_owner_user_discovery");
    else if(symptomCategoryVar == remote_desktop_protocol)
        return std::string("remote_desktop_protocol");
    else if(symptomCategoryVar == domain_generation_algorithms)
        return std::string("domain_generation_algorithms");
    else if(symptomCategoryVar == fallback_channels)
        return std::string("fallback_channels");
    else if(symptomCategoryVar == standart_application_layer_protocol)
        return std::string("standart_application_layer_protocol");
    else if(symptomCategoryVar == custom)
        return std::string("custom");
}
