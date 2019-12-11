#ifndef SYSTEM_NETWORK_CONN_DISCOVERY_HPP
#define SYSTEM_NETWORK_CONN_DISCOVERY_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class SystemNetworkConnDiscoverySymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            SystemNetworkConnDiscoverySymptoms(std::string filename);
            SystemNetworkConnDiscoverySymptoms(const SystemNetworkConnDiscoverySymptoms &other) = default;
            SystemNetworkConnDiscoverySymptoms(SystemNetworkConnDiscoverySymptoms &&other) = default;
            ~SystemNetworkConnDiscoverySymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
