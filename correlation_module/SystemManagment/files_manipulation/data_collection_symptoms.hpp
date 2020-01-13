#ifndef DATA_COLLECTION_SYMPTOMS_HPP
#define DATA_COLLECTION_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

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
