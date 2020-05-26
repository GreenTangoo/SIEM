#ifndef PORT_SCANNING_SYMPTOMS_HPP
#define PORT_SCANNING_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace discovery
    {
        class PortScanningSymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
        public:
            PortScanningSymptoms(std::string filename);
            PortScanningSymptoms(const PortScanningSymptoms &other) = default;
            PortScanningSymptoms(PortScanningSymptoms &&other) = default;
            ~PortScanningSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
