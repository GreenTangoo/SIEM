#ifndef ACCOUNT_DISCOVERY_SYMPTOMS_HPP
#define ACCOUNT_DISCOVERY_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace files_manipulation
    {
        class AccountDiscoverySymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
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
