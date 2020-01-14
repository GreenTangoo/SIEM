#ifndef PROCESS_DISCOVERY_SYMPTOMS_HPP
#define PROCESS_DISCOVERY_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class ProcessDiscoverySymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
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
