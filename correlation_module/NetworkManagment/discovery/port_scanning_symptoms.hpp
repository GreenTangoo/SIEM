#ifndef PORT_SCANNING_SYMPTOMS_HPP
#define PORT_SCANNING_SYMPTOMS_HPP

#include <fstream>
#include <string>

#include "../../symptoms_interface/main_symp_interface.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace discovery
    {
        class PortScanningSymptoms : public Symptom
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
            std::string warning_msg();
        };
    }
}

#endif
