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

    jsoner_space::JsonContainer *container = parser.findElementByName("iptables");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;

    std::map<std::string, int32_t> ipAmountReq;
    for(; container != nullptr; container = container->next)
    {
        std::string ipAddr = container->oneCell.first;
        ipAmountReq[ipAddr]++;
    }

    for(std::map<std::string, int32_t>::iterator it = ipAmountReq.begin(); it != ipAmountReq.end(); it++)
    {
        if(it->second > 2)
        {
            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(it->first, 1));
            jsoner_space::JsonContainer *anchor = parser.findElementByName(it->first);
            dataObj.time = data_time_space::Time(anchor->down->oneCell.second);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}

