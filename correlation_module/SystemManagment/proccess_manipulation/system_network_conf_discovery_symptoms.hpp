#ifndef SYSTEM_NETWORK_CONF_DISCOVERY_SYMPTOMS_HPP
#define SYSTEM_NETWORK_CONF_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class SystemNetworkConfDiscoverySymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            SystemNetworkConfDiscoverySymptoms(std::string filename);
            SystemNetworkConfDiscoverySymptoms(const SystemNetworkConfDiscoverySymptoms &other) = default;
            SystemNetworkConfDiscoverySymptoms(SystemNetworkConfDiscoverySymptoms &&other) = default;
            ~SystemNetworkConfDiscoverySymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
