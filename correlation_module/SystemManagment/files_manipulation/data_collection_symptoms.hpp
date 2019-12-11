#ifndef DATA_COLLECTION_SYMPTOMS_HPP
#define DATA_COLLECTION_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace files_manipulation
    {
        class DataCollectionSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            DataCollectionSymptoms(std::string filename);
            DataCollectionSymptoms(const DataCollectionSymptoms &other) = default;
            DataCollectionSymptoms(DataCollectionSymptoms &&other) = default;
            ~DataCollectionSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
