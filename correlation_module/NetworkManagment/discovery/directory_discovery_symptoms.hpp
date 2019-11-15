#ifndef DIRECTORY_DISCOVERY_SYMPTOMS_HPP
#define DIRECTORY_DISCOVERY_SYMPTOMS_HPP

#include <fstream>
#include <string>

#include "../../symptoms_interface/main_symp_interface.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace discovery
    {
        class DirectoryDiscoverySymptoms : public Symptom
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            DirectoryDiscoverySymptoms(std::string filename);
            DirectoryDiscoverySymptoms(const DirectoryDiscoverySymptoms &other) = default;
            DirectoryDiscoverySymptoms(DirectoryDiscoverySymptoms &&other) = default;
            ~DirectoryDiscoverySymptoms();
            bool checkSymptoms();
            std::string warning_msg();
            data getData();
        };
    }
}

#endif
