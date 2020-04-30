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

    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;
    for(; container != nullptr; container = container->next)
    {
        std::string openedFilename = container->down->oneCell.first;

        if(openedFilename == "passwd")
        {
            std::string name = container->oneCell.first;
            std::string filename = container->down->oneCell.first;
            std::string actinoPrefix = container->down->down->next->oneCell.first;
            std::string action = container->down->down->next->oneCell.second;
            std::string privilegesPrefix = container->down->down->next->next->oneCell.first;
            std::string privileges = container->down->down->next->next->oneCell.second;
            std::string time = container->down->down->oneCell.second;

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
