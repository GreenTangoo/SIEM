#include "command_line_interface_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;


CommandLineInterfaceSymptoms::CommandLineInterfaceSymptoms(std::string filename) : jsonFilename(filename)
{
    this->typeSymp = category_space::symptomCategory::command_line_interface;
}

CommandLineInterfaceSymptoms::~CommandLineInterfaceSymptoms()
{

}

bool CommandLineInterfaceSymptoms::checkSymptoms()
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
        std::string processName = container->childNode->keyValue.first;
        std::string processAction = container->childNode->childNode->nextNode->keyValue.second;

        if((processName == "bash") &&
                (processAction == "start"))
        {
            std::string username = container->keyValue.first;
            std::string actionPrefix = container->childNode->childNode->nextNode->keyValue.first;
            std::string privilegesPrefix = container->childNode->childNode->nextNode->nextNode->keyValue.first;
            std::string privileges = container->childNode->childNode->nextNode->nextNode->keyValue.second;
            std::string time = container->childNode->childNode->keyValue.second;

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
