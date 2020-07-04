#include "system_network_conf_discovery_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;

#define IFCONFIG "ifconfig"

SystemNetworkConfDiscoverySymptoms::SystemNetworkConfDiscoverySymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::system_network_configuration_discovery;
}

SystemNetworkConfDiscoverySymptoms::~SystemNetworkConfDiscoverySymptoms()
{

}

bool SystemNetworkConfDiscoverySymptoms::checkSymptoms()
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
        std::shared_ptr<JsonContainer> confDiscoveryNodePtr = parser.findElementByPath("/" + username + "/" + IFCONFIG);

        if(confDiscoveryNodePtr)
        {
            std::string discoverConfProgram = confDiscoveryNodePtr->keyValue.first;
            std::string argsProgram = confDiscoveryNodePtr->keyValue.second;

            Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(discoverConfProgram, 0));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(argsProgram, 0));
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
