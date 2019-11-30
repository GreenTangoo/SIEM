#ifndef ALL_CATEGORIES_HPP
#define ALL_CATEGORIES_HPP

#include <string>

namespace category
{
    enum symptom_category
    {
        user_login, login_root, directory_discovery, port_scanning,
        action_files, action_proccesses, escalation_priv
    };
    static std::string getCategoryName(symptom_category symptom_category)
    {
        if(symptom_category == user_login)
            return std::string("user_login");
        if(symptom_category == login_root)
            return std::string("login_root");
        if(symptom_category == directory_discovery)
            return std::string("directory_discovery");
        if(symptom_category == port_scanning)
            return std::string("port_scanning");
        if(symptom_category == action_files)
            return std::string("action_files");
        if(symptom_category == action_proccesses)
            return std::string("action_proccesses");
        if(symptom_category == escalation_priv)
            return std::string("escalation_priv");
    }
}

#endif
