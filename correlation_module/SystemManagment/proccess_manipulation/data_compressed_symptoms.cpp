#include "data_compressed_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;


DataCompressedSymptoms::DataCompressedSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::data_compressed;
}

DataCompressedSymptoms::~DataCompressedSymptoms()
{

}

bool DataCompressedSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    std::shared_ptr<JsonContainer> container = parser.findElementByName("users");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;
    if(container->typeNode == json_space::NONE)
        return false;

    for(; container->childNode != nullptr; container->childNode = container->childNode->nextNode)
    {
        std::string processName = container->childNode->keyValue.first;
        std::string actionName = container->childNode->childNode->nextNode->keyValue.second;

        if(((processName == "tar") || (processName == "gzip") || (processName == "7z")) &&
                (actionName == "start"))
        {
            symptoms_space::Data dataObj;
            std::string name = container->keyValue.first;
            std::string actionPrefix = container->childNode->childNode->nextNode->keyValue.first;
            std::string privilegesPrefix = container->childNode->childNode->nextNode->nextNode->keyValue.first;
            std::string privilegesName = container->childNode->childNode->nextNode->nextNode->keyValue.second;
            std::string time = container->childNode->childNode->keyValue.second;

            dataObj.mainData.push_back(std::pair<std::string, int16_t>(name, 1)); // Get name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(processName, 0)); // Get process name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actionPrefix + ":" + actionName, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privilegesName, 0)); // Get privilieges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
