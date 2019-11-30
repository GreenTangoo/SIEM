#ifndef DIRECTORY_DISCOVERY_SYMPTOMS_HPP
#define DIRECTORY_DISCOVERY_SYMPTOMS_HPP

#include <string>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace discovery
    {
        class DirectoryDiscoverySymptoms : public Symptom_impl
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
        };
    }
}

#endif
