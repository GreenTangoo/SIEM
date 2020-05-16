#ifndef CUSTOM_CORRELATOR
#define CUSTOM_CORRELATOR

#include "config_descriptor.hpp"
#include "../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace custom_correlation
    {
        class CustomSymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
            OneConfigCell jsonConfigCell;
        private:
            bool isTemplate(std::string valueString);
            bool foundByConfig(OneConfigCell cellConfig, jsoner_space::JsonParser &parserJson, Data &dataObj);
            bool amountByConfig(OneConfigCell cellConfig, jsoner_space::JsonParser &parserJson);
            std::string addDataAndPriority(std::string data, Data &dataObj);
            std::vector<std::pair<std::string, std::string>>::const_iterator foundInVec(const std::vector<std::pair<std::string, std::string>> &vec, std::string value);
        public:
            CustomSymptoms(OneConfigCell cellObj);
            CustomSymptoms(const CustomSymptoms &other) = default;
            CustomSymptoms(CustomSymptoms &&other) = default;
            ~CustomSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif // CUSTOM_CORRELATOR
