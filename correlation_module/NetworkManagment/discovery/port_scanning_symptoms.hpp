#ifndef PORT_SCANNING_SYMPTOMS_HPP
#define PORT_SCANNING_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace discovery
    {
        class PortScanningSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
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
