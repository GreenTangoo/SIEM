#include "directory_discovery_symptoms.hpp"

using namespace symptoms_space::discovery;

#define RESPONSE_404 "response-code-404"

DirectoryDiscoverySymptoms::DirectoryDiscoverySymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::directory_discovery;
}

DirectoryDiscoverySymptoms::~DirectoryDiscoverySymptoms()
{

}

bool DirectoryDiscoverySymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    std::shared_ptr<JsonContainer> container = parser.findElementByName("requests");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;
    if(container->typeNode == json_space::NONE)
        return false;

    std::map<std::string, int32_t> ipAmountReq;
    for(; container != nullptr; container = container->nextNode)
    {
        std::string ipAddr = container->keyValue.first;
        std::shared_ptr<JsonContainer> respCodeContainer = parser.findElementByPath(ipAddr + "/" + RESPONSE_404);
        if(respCodeContainer != nullptr)
        {
            int amountBadResponse = atoi(respCodeContainer->keyValue.second.c_str());
            ipAmountReq[ipAddr] = amountBadResponse;
        }
    }
    for(std::map<std::string, int32_t>::iterator it = ipAmountReq.begin(); it != ipAmountReq.end(); it++)
        if(it->second > 2)
        {
            symptoms_space::Data data_obj;
            data_obj.mainData.push_back(std::pair<std::string, int16_t>(it->first, 1));
            std::shared_ptr<JsonContainer> anchorIpNode = parser.findElementByPath(it->first + "/" + "time");
            data_obj.time = data_time_space::Time(anchorIpNode->keyValue.second);
            data_obj.isUsed = false;
            this->allDataFromSymptom.push_back(data_obj);
        }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
