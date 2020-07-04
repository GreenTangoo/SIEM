#include "command_line_interface_symptoms.hpp"

using namespace symptoms_space::proccess_manipulation;

#define BASH "bash"
#define KSH "ksh"
#define ZSH "zsh"

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
        std::string username = container->keyValue.first;
        std::shared_ptr<JsonContainer> intrepreterNodePtr = parser.findElementByPath("/" + username + "/" + BASH);
        if(intrepreterNodePtr)
        {
            std::string programName = intrepreterNodePtr->keyValue.first;
            std::string argsProgram = intrepreterNodePtr->keyValue.second;

            Data dataObj;
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(username, 1));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(programName, 0));
            dataObj.mainData.push_back(std::pair<std::string, int16_t>(argsProgram, 0));
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }

    if(this->allDataFromSymptom.size() > 0)
        return true;
    else return false;
}
