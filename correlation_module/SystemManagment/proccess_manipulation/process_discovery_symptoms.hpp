#ifndef PROCESS_DISCOVERY_SYMPTOMS_HPP
#define PROCESS_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace proccess_manipulation
    {
        class ProcessDiscoverySymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
        public:
            ProcessDiscoverySymptoms(std::string filename);
            ProcessDiscoverySymptoms(const ProcessDiscoverySymptoms &other) = default;
            ProcessDiscoverySymptoms(ProcessDiscoverySymptoms &&other) = default;
            ~ProcessDiscoverySymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
