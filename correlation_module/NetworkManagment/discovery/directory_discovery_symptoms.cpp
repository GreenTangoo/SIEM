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

    jsoner_space::JsonContainer *container = parser.findElementByName("requests");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;

    std::map<std::string, int32_t> ipAmountReq;
    for(; container != nullptr; container = container->next)
    {
        std::string responseCode = container->down->next->oneCell.second;
        std::string ipAddr = container->oneCell.first;

        if(responseCode == "404")
            ipAmountReq[ipAddr]++;
    }
    for(std::map<std::string, int32_t>::iterator it = ipAmountReq.begin(); it != ipAmountReq.end(); it++)
        if(it->second > 2)
        {
            symptoms_space::Data data_obj;
            data_obj.mainData.push_back(std::pair<std::string, int16_t>(it->first, 1));
            jsoner_space::JsonContainer *anchor = parser.findElementByName(it->first);
            data_obj.time = data_time_space::Time(anchor->down->oneCell.second);
            data_obj.isUsed = false;
            this->allDataFromSymptom.push_back(data_obj);
        }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
