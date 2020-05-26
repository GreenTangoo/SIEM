#ifndef DIRECTORY_DISCOVERY_SYMPTOMS_HPP
#define DIRECTORY_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace discovery
    {
        class DirectoryDiscoverySymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
        public:
            DirectoryDiscoverySymptoms(std::string filename);
            DirectoryDiscoverySymptoms(const DirectoryDiscoverySymptoms &other) = default;
            DirectoryDiscoverySymptoms(DirectoryDiscoverySymptoms &&other) = default;
            ~DirectoryDiscoverySymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
