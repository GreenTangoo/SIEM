#ifndef ALL_CATEGORIES_HPP
#define ALL_CATEGORIES_HPP

#include <string>

namespace category
{
    enum symptom_category
    {
        user_login, login_root, directory_discovery, port_scanning, command_line_interface,
        account_discovery, process_discovery, system_network_configuration_discovery,
        system_network_connection_discovery, data_collection, data_compressed
    };
    class category_resolver // SINGLETON
    {
    private:
        category_resolver();
        category_resolver(const category_resolver &other) = delete;
        category_resolver(category_resolver &&other) = delete;
        category_resolver& operator=(const category_resolver &other) = delete;
    public:
        static category_resolver& getInstance();
        std::string getCategoryName(symptom_category symptom_cat);
    };
}

#endif
