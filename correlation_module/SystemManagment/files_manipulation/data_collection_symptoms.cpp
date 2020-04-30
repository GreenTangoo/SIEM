#include "data_collection_symptoms.hpp"

using namespace symptoms_space::files_manipulation;


DataCollectionSymptoms::DataCollectionSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::data_collection;
}

DataCollectionSymptoms::~DataCollectionSymptoms()
{

}

bool DataCollectionSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;
    for(; container->down != nullptr; container->down = container->down->next)
    {
        std::string actionWithFile = container->down->down->next->oneCell.second;

        if(actionWithFile == "download")
        {
            std::string username = container->oneCell.first;
            std::string filename = container->down->oneCell.first;
            std::string actionPrefix = container->down->down->next->oneCell.first;
            std::string action = container->down->down->next->oneCell.second;
            std::string privilegesPrefix = container->down->down->next->next->oneCell.first;
            std::string privileges = container->down->down->next->next->oneCell.second;
            std::string time = container->down->down->oneCell.second;

            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1)); // Get username
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(filename, 0)); // Get filename
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actionPrefix + ":" + action, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privileges, 0)); // Get privielieges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
