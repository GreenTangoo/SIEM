#ifndef DATA_COLLECTION_SYMPTOMS_HPP
#define DATA_COLLECTION_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace files_manipulation
    {
        class DataCollectionSymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
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
