#ifndef ALL_CATEGORIES_HPP
#define ALL_CATEGORIES_HPP

namespace category
{
    namespace AccessManagmentSpace
    {
        enum account_acces_enum
        {
            user_login
        };
    }
    namespace AvaiabilityManagmentSpace
    {
        enum denial_of_service
        {
            dos_wifi
        };
    }
    namespace NetworkManagmentSpace
    {
        enum discovery_enum
        {
            directory_discovery, port_scanning
        };
    }
}

#endif
