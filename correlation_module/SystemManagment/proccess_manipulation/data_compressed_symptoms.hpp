#ifndef DATA_COMPRESSED_SYMPTOMS_HPP
#define DATA_COMPRESSED_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace proccess_manipulation
    {
        class DataCompressedSymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
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
