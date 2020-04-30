#include "user_login_symptoms.hpp"

using namespace symptoms_space::account_access;


UserLoginSymptoms::UserLoginSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::user_login;
}

UserLoginSymptoms::~UserLoginSymptoms()
{

}

bool UserLoginSymptoms::checkSymptoms()
{
    parser = getJsonData(jsonFilename);
    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;

    for(; container != nullptr; container = container->next)
    {
        std::string username = container->oneCell.first;
        std::string ip = container->down->next->oneCell.second;
        std::string time = container->down->oneCell.second;

        symptoms_space::Data data_obj;
        data_obj.mainData.push_back(std::pair<std::string, int16_t>(username, 1)); // Get username
        data_obj.mainData.push_back(std::pair<std::string, int16_t>(ip, 1)); // Get ip
        data_obj.time = data_time_space::Time(time);
        data_obj.isUsed = false;
        this->allDataFromSymptom.push_back(data_obj);
    }
    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
