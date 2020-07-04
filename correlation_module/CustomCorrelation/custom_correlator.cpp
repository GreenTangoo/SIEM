#include "custom_correlator.hpp"

using namespace symptoms_space::custom_correlation;

#define JSON_PATH_NODE_INDEX 0
#define PARSE_TYPE_INDEX 1
#define CORRECT_DATA_PRIORITY_FORMAT 2

#define FOUND_PARSE_TYPE "found"
#define AMOUNT_PARSE_TYPE "amount"

#define SUCCESSFULL_FOUNDED true
#define SUCCESSFULL_AMOUNT true

CustomSymptoms::CustomSymptoms(OneConfigCell cellObj) : jsonConfigCell(cellObj)
{
    this->typeSymp = category_space::symptomCategory::custom;
}

CustomSymptoms::~CustomSymptoms()
{

}

bool CustomSymptoms::checkSymptoms()
{
    jsonFilename = jsonConfigCell.keyValues[JSON_PATH_NODE_INDEX].second;
    parser = getJsonData(jsonFilename);

    std::string parseType = jsonConfigCell.keyValues[PARSE_TYPE_INDEX].second;
    if(parseType == FOUND_PARSE_TYPE)
    {
        symptoms_space::Data dataObj;
        bool result = foundByConfig(this->jsonConfigCell, parser, dataObj);

        if(result != SUCCESSFULL_FOUNDED)
        {
            return false;
        }
        else
        {
            dataObj.isUsed = false;
            this->allDataFromSymptom.push_back(dataObj);
        }
    }
    else if(parseType == AMOUNT_PARSE_TYPE)
    {
        bool result = amountByConfig(this->jsonConfigCell, parser);

        if(result != SUCCESSFULL_AMOUNT)
        {
            return false;
        }
        else
        {

        }
    }
    else
    {
        throw SIEM_errors::SIEMException("Incorrect parsing type in config file(correlation)");
    }

    return true;
}


std::string CustomSymptoms::addDataAndPriority(std::string data, Data &dataObj)
{
    data = parser_string_space::delete_symbol(data, parser_string_space::SPACE);

    std::list<std::string> dataPriority = parser_string_space::parse_by_delimeter(data, "|");

    if(dataPriority.size() != CORRECT_DATA_PRIORITY_FORMAT)
    {
        return data;
    }

    std::list<std::string>::iterator dataIter = std::next(dataPriority.begin(), 0);
    std::list<std::string>::iterator priorityIter = std::next(dataPriority.begin(), 1);

    uint16_t priorityNumber = static_cast<uint16_t>(std::stoi(*priorityIter));

    dataObj.mainData.push_back(std::pair<std::string, uint16_t>(*dataIter, priorityNumber));

    return *dataIter;
}

std::vector<std::pair<std::string, std::string>>::const_iterator CustomSymptoms::foundInVec(const std::vector<std::pair<std::string, std::string>> &vec, std::string value)
{
    std::vector<std::pair<std::string, std::string>>::const_iterator foundedIt =
            std::find_if(vec.begin(), vec.end(), [&value](const std::pair<std::string, std::string> &elem)
    {
        return elem.first == value;
    });

    return foundedIt;
}

bool CustomSymptoms::foundByConfig(OneConfigCell cellConfig, json_space::JsonObject &parserJson, symptoms_space::Data &dataObj)
{
    std::vector<std::pair<std::string, std::string>>::const_iterator keyIt =
            foundInVec(cellConfig.keyValues, KEY_VALUE);

    if(keyIt == cellConfig.keyValues.end())
    {
        return false;
    }

    std::string keyValue = addDataAndPriority(keyIt->second, dataObj);

    std::shared_ptr<JsonContainer> container = parserJson.findElementByName(keyValue);
    if(container == nullptr)
    {
        return false;
    }

    std::vector<std::pair<std::string, std::string>>::const_iterator typeNodeIt =
            foundInVec(cellConfig.keyValues, TYPE_NODE);

    if(typeNodeIt == cellConfig.keyValues.end())
    {
        return false;
    }

    json_space::typeNodeJSON typeNode = json_space::JSONNodeTypeResolver::getInstance().getNodeType(typeNodeIt->second);

    if(container->typeNode != typeNode)
        return false;

    if(typeNode == json_space::STRING)
    {
        std::vector<std::pair<std::string, std::string>>::const_iterator parameterIt =
                foundInVec(cellConfig.keyValues, PARAMETER_VALUE);
        if(parameterIt != cellConfig.keyValues.end())
        {
            std::string parameterValue = addDataAndPriority(parameterIt->second, dataObj);
            if(container->keyValue.second != parameterValue)
                return false;
        }
    }

    if(cellConfig.andConditionCellPtr != nullptr)
    {
        OneConfigCell andConditionalConfig(*(cellConfig.andConditionCellPtr.get()));
        json_space::JsonObject andCondParser(*(container->parentNode.get()));
        if(foundByConfig(andConditionalConfig, andCondParser, dataObj) == false)
            return false;
    }

    if(cellConfig.innerCellPtr != nullptr)
    {
        if(container->childNode == nullptr)
            return false;

        OneConfigCell innerConditionalCell(*(cellConfig.innerCellPtr.get()));
        json_space::JsonObject innerCondParser(*(container->childNode.get()));
        if(foundByConfig(innerConditionalCell, innerCondParser, dataObj) == false)
            return false;
    }

    return true;
}

bool CustomSymptoms::amountByConfig(OneConfigCell cellConfig, json_space::JsonObject &parserJson)
{

}
