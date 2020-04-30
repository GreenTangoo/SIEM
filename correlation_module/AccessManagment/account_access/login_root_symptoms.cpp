#include "login_root_symptoms.hpp"

using namespace symptoms_space::account_access;


LoginRootSymptoms::LoginRootSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::login_root;
}

LoginRootSymptoms::~LoginRootSymptoms()
{

}

bool LoginRootSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);
    jsoner_space::JsonContainer *container = parser.findElementByName("root");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;

    for(; container != nullptr; container = container->next)
    {
        if(container->down->next->oneCell.second == "denied")
        {
            std::string username = container->oneCell.first;
            std::string result = container->down->next->oneCell.second;
            std::string time = container->down->oneCell.second;

            symptoms_space::Data data_obj;
            data_obj.mainData.push_back(std::pair<std::string, int16_t>(username ,1)); // Get username
            data_obj.mainData.push_back(std::pair<std::string, int16_t>(result, 0)); // Get result
            data_obj.time = data_time_space::Time(time);
            data_obj.isUsed = false;
            this->allDataFromSymptom.push_back(data_obj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
