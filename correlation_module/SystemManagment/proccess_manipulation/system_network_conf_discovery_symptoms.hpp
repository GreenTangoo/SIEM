#ifndef SYSTEM_NETWORK_CONF_DISCOVERY_SYMPTOMS_HPP
#define SYSTEM_NETWORK_CONF_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace proccess_manipulation
    {
        class SystemNetworkConfDiscoverySymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
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
