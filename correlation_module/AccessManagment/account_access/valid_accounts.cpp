#include "valid_accounts.hpp"

using namespace symptoms_space::account_access;


ValidAccountsSymptoms::ValidAccountsSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::login_root;
}

ValidAccountsSymptoms::~ValidAccountsSymptoms()
{

}

bool ValidAccountsSymptoms::checkSymptoms()
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
        std::string authTime = container->childNode->keyValue.second;
        data_time_space::Time authTimeObj(authTime);

        if((authTimeObj.getAbsoluteTime() > data_time_space::Time::getAbsoluteTime("23:00:00"))
                || (authTimeObj.getAbsoluteTime() < data_time_space::Time::getAbsoluteTime("8:00:00")))
        {
            std::string username = container->keyValue.first;

            symptoms_space::Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(authTime, 0));
            dataObj.time = data_time_space::Time(authTime);
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
