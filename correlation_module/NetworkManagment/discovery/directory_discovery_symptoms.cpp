#include "directory_discovery_symptoms.hpp"

using namespace symptoms_space::discovery;


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
        std::string responseCode = container->childNode->nextNode->keyValue.second;
        std::string ipAddr = container->keyValue.first;

        if(responseCode == "404")
            ipAmountReq[ipAddr]++;
    }
    for(std::map<std::string, int32_t>::iterator it = ipAmountReq.begin(); it != ipAmountReq.end(); it++)
        if(it->second > 2)
        {
            symptoms_space::Data data_obj;
            data_obj.mainData.push_back(std::pair<std::string, int16_t>(it->first, 1));
            std::shared_ptr<JsonContainer> anchor = parser.findElementByName(it->first);
            data_obj.time = data_time_space::Time(anchor->childNode->keyValue.second);
            data_obj.isUsed = false;
            this->allDataFromSymptom.push_back(data_obj);
        }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
