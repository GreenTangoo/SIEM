#ifndef DATA_COMPRESSED_SYMPTOMS_HPP
#define DATA_COMPRESSED_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class DataCompressedSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            DataCompressedSymptoms(std::string filename);
            DataCompressedSymptoms(const DataCompressedSymptoms &other) = default;
            DataCompressedSymptoms(DataCompressedSymptoms &&other) = default;
            ~DataCompressedSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
