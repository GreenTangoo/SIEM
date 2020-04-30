#ifndef ACCOUNT_DISCOVERY_SYMPTOMS_HPP
#define ACCOUNT_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace files_manipulation
    {
        class AccountDiscoverySymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
        public:
            AccountDiscoverySymptoms(std::string filename);
            AccountDiscoverySymptoms(const AccountDiscoverySymptoms &other) = default;
            AccountDiscoverySymptoms(AccountDiscoverySymptoms &&other) = default;
            ~AccountDiscoverySymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
