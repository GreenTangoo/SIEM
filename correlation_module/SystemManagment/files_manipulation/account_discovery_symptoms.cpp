#include "account_discovery_symptoms.hpp"

using namespace symptoms_space::files_manipulation;


AccountDiscoverySymptoms::AccountDiscoverySymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::account_discovery;
}

AccountDiscoverySymptoms::~AccountDiscoverySymptoms()
{

}

bool AccountDiscoverySymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    std::shared_ptr<JsonContainer> container = parser.findElementByName("users");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;
    if(container->typeNode == json_space::NONE)
        return false;

    for(; container != nullptr; container = container->nextNode)
    {
        std::string openedFilename = container->childNode->keyValue.first;

        if(openedFilename == "passwd")
        {
            std::string name = container->keyValue.first;
            std::string filename = container->childNode->keyValue.first;
            std::string actinoPrefix = container->childNode->childNode->nextNode->keyValue.first;
            std::string action = container->childNode->childNode->nextNode->keyValue.second;
            std::string privilegesPrefix = container->childNode->childNode->nextNode->nextNode->keyValue.first;
            std::string privileges = container->childNode->childNode->nextNode->nextNode->keyValue.second;
            std::string time = container->childNode->childNode->keyValue.second;

            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(name, 1)); // Get name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(filename, 0)); // Get filename
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actinoPrefix + ":" + action, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privileges, 0)); // Get privieleges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
