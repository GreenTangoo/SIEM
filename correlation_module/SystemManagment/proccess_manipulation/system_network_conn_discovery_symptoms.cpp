#include "system_network_conn_discovery_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;


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

    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;
    for(; container->down != nullptr; container->down = container->down->next)
    {
        std::string processName = container->down->oneCell.first;
        std::string processAction = container->down->down->next->oneCell.second;

        if(((processName == "netstat") || (processName == "lsof") || (processName == "w")) &&
                (processAction == "start"))
        {
            std::string username = container->oneCell.first;
            std::string actionPrefix = container->down->down->next->oneCell.first;
            std::string privilegesPrefix = container->down->down->next->next->oneCell.first;
            std::string privileges = container->down->down->next->next->oneCell.second;
            std::string time = container->down->down->oneCell.second;

            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1)); // Get name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(processName, 0)); // Get process name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actionPrefix + ":" + processAction, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privileges, 0)); // Get privilieges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
