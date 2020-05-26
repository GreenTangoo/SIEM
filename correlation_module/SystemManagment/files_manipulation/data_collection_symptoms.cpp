#include "data_collection_symptoms.hpp"

using namespace symptoms_space::files_manipulation;


DataCollectionSymptoms::DataCollectionSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::data_collection;
}

DataCollectionSymptoms::~DataCollectionSymptoms()
{

}

bool DataCollectionSymptoms::checkSymptoms()
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
        std::string actionWithFile = container->childNode->childNode->nextNode->keyValue.second;

        if(actionWithFile == "download")
        {
            std::string username = container->keyValue.first;
            std::string filename = container->childNode->keyValue.first;
            std::string actionPrefix = container->childNode->childNode->nextNode->keyValue.first;
            std::string action = container->childNode->childNode->nextNode->keyValue.second;
            std::string privilegesPrefix = container->childNode->childNode->nextNode->nextNode->keyValue.first;
            std::string privileges = container->childNode->childNode->nextNode->nextNode->keyValue.second;
            std::string time = container->childNode->childNode->keyValue.second;

            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1)); // Get username
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(filename, 0)); // Get filename
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actionPrefix + ":" + action, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privileges, 0)); // Get privielieges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
