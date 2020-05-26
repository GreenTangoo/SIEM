#ifndef SYSTEM_NETWORK_CONN_DISCOVERY_HPP
#define SYSTEM_NETWORK_CONN_DISCOVERY_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace proccess_manipulation
    {
        class SystemNetworkConnDiscoverySymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
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
