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
    std::shared_ptr<JsonContainer> container = parser.findElementByName("root");

    if((container == nullptr) || (container->childNode == nullptr))
        return false;

    container = container->childNode;

    if(container->typeNode == json_space::NONE)
        return false;

    for(; container != nullptr; container = container->nextNode)
    {
        if(container->childNode->nextNode->keyValue.second == "denied")
        {
            std::string username = container->keyValue.first;
            std::string result = container->childNode->nextNode->keyValue.second;
            std::string time = container->childNode->keyValue.second;

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
