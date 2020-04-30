#include "data_compressed_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;


DataCompressedSymptoms::DataCompressedSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::data_compressed;
}

DataCompressedSymptoms::~DataCompressedSymptoms()
{

}

bool DataCompressedSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);

    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;
    for(; container->down != nullptr; container->down = container->down->next)
    {
        std::string processName = container->down->oneCell.first;
        std::string actionName = container->down->down->next->oneCell.second;

        if(((processName == "tar") || (processName == "gzip") || (processName == "7z")) &&
                (actionName == "start"))
        {
            symptoms_space::Data dataObj;
            std::string name = container->oneCell.first;
            std::string actionPrefix = container->down->down->next->oneCell.first;
            std::string privilegesPrefix = container->down->down->next->next->oneCell.first;
            std::string privilegesName = container->down->down->next->next->oneCell.second;
            std::string time = container->down->down->oneCell.second;

            dataObj.mainData.push_back(std::pair<std::string, int16_t>(name, 1)); // Get name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(processName, 0)); // Get process name
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(actionPrefix + ":" + actionName, 0)); // Get action
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(privilegesPrefix + ":" + privilegesName, 0)); // Get privilieges
            dataObj.time = data_time_space::Time(time);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
