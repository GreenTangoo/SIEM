#include "port_scanning_symptoms.hpp"

using namespace symptoms_space::discovery;


PortScanningSymptoms::PortScanningSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::port_scanning;
}

PortScanningSymptoms::~PortScanningSymptoms()
{

}

bool PortScanningSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    std::shared_ptr<JsonContainer> container = parser.findElementByName("iptables");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;
    if(container->typeNode == json_space::NONE)
        return false;

    std::map<std::string, int32_t> ipAmountReq;
    for(; container != nullptr; container = container->nextNode)
    {
        std::string ipAddr = container->keyValue.first;
        ipAmountReq[ipAddr]++;
    }

    for(std::map<std::string, int32_t>::iterator it = ipAmountReq.begin(); it != ipAmountReq.end(); it++)
    {
        if(it->second > 2)
        {
            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(it->first, 1));
            std::shared_ptr<JsonContainer> dstIp = parser.findElementByPath(it->first + "/" + "dst-ip");
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(dstIp->keyValue.second, 1));
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}

