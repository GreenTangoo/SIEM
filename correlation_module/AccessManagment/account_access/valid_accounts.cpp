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
    jsoner_space::JsonContainer *container = parser.findElementByName("users");
    container = container->down;
    if(container->cellType == jsoner_space::NONE)
        return false;

    for(; container != nullptr; container = container->next)
    {
        std::string authTime = container->down->oneCell.second;
        data_time_space::Time authTimeObj(authTime);

        if((authTimeObj.getAbsoluteTime() > data_time_space::Time::getAbsoluteTime("23:00:00"))
                || (authTimeObj.getAbsoluteTime() < data_time_space::Time::getAbsoluteTime("8:00:00")))
        {
            std::string username = container->oneCell.first;

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
