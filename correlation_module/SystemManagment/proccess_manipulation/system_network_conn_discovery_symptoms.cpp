#include "system_network_conn_discovery_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;

#define NETSTAT "netstat"

SystemNetworkConnDiscoverySymptoms::SystemNetworkConnDiscoverySymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::system_network_connection_discovery;
}

SystemNetworkConnDiscoverySymptoms::~SystemNetworkConnDiscoverySymptoms()
{

}

bool SystemNetworkConnDiscoverySymptoms::checkSymptoms()
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
        std::shared_ptr<JsonContainer> connectDiscoveryNodePtr = parser.findElementByPath("/" + username + "/" + NETSTAT);

        if(connectDiscoveryNodePtr)
        {
            std::string connDiscoveryProgram = connectDiscoveryNodePtr->keyValue.first;
            std::string argsProgram = connectDiscoveryNodePtr->keyValue.second;

            Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(connDiscoveryProgram, 0));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(argsProgram, 0));
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
