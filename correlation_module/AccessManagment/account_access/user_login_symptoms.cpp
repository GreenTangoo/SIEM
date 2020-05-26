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
    std::shared_ptr<JsonContainer> container = parser.findElementByName("users");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;

    if(container->typeNode == json_space::NONE)
        return false;

    for(; container != nullptr; container = container->nextNode)
    {
        std::string username = container->keyValue.first;
        std::string ip = container->childNode->nextNode->keyValue.second;
        std::string time = container->childNode->keyValue.second;

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
