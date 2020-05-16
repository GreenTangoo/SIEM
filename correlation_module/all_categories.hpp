#ifndef ALL_CATEGORIES_HPP
#define ALL_CATEGORIES_HPP

#include <string>

namespace category_space
{

    enum symptomPriority
    {
        no_priority = 0, priority_1 = 1, priority_2 = 2
    };

    enum symptomCategory
    {
        user_login, login_root, directory_discovery, port_scanning, command_line_interface,
        account_discovery, process_discovery, system_network_configuration_discovery,
        system_network_connection_discovery, data_collection, data_compressed,
        external_remote_services, spearphishing_attachment, supply_chain_compromise,
        valid_accounts, compiled_html_file, exploitation_for_client_execution,
        powershell, scheduled_task, windows_managment_instrumentation,
        accesebility_features, bootkit, create_account, modify_existing_services,
        registry_run_keys_startup_folder, process_injection, code_signing,
        connection_proxy, dll_side_loading, file_deletion, indicator_removal_on_host,
        masquerading, modify_registry, rootkit, web_service, credential_dumping,
        input_capture, network_share_discovery, network_service_scanning,
        system_owner_user_discovery, remote_desktop_protocol, domain_generation_algorithms,
        fallback_channels, standart_application_layer_protocol, custom
    };
    class CategoryResolver // SINGLETON
    {
    private:
        CategoryResolver();
        CategoryResolver(const CategoryResolver &other) = delete;
        CategoryResolver(CategoryResolver &&other) = delete;
        CategoryResolver& operator=(const CategoryResolver &other) = delete;
    public:
        static CategoryResolver& getInstance();
        std::string getCategoryName(symptomCategory symptomCategoryVar);
    };
}

#endif
