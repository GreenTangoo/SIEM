#include "process_discovery_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;

#define PS "ps"

ProcessDiscoverySymptoms::ProcessDiscoverySymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::process_discovery;
}

ProcessDiscoverySymptoms::~ProcessDiscoverySymptoms()
{

}

bool ProcessDiscoverySymptoms::checkSymptoms()
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
        std::string username = container->keyValue.first;
        std::shared_ptr<JsonContainer> discoveryProgrNodePtr = parser.findElementByPath("/" + username + "/" + PS);

        if(discoveryProgrNodePtr)
        {
            std::string discoveryProgram = discoveryProgrNodePtr->keyValue.first;
            std::string argsProgram = discoveryProgrNodePtr->keyValue.second;

            Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(discoveryProgram, 0));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(argsProgram, 0));
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
