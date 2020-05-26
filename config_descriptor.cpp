#include "config_descriptor.hpp"


using namespace config_space;

OneConfigCell::OneConfigCell()
{
}

OneConfigCell::OneConfigCell(const OneConfigCell &other)
{
    std::copy(other.keyValues.begin(), other.keyValues.end(), std::back_inserter(keyValues));

    if(other.innerCellPtr != nullptr)
    {
        innerCellPtr = std::make_shared<OneConfigCell>();
        *(innerCellPtr.get()) = *(other.innerCellPtr.get());
    }
    if(other.andConditionCellPtr != nullptr)
    {
        andConditionCellPtr = std::make_shared<OneConfigCell>();
        *(andConditionCellPtr.get()) = *(other.andConditionCellPtr.get());
    }
}

OneConfigCell::OneConfigCell(OneConfigCell &&other)
{
    std::copy(other.keyValues.begin(), other.keyValues.end(), std::back_inserter(keyValues));
    other.keyValues.clear();

    *(innerCellPtr.get()) = *(other.innerCellPtr.get());
    other.innerCellPtr.reset();

    *(andConditionCellPtr.get()) = *(other.innerCellPtr.get());
    other.innerCellPtr.reset();
}

OneConfigCell::~OneConfigCell()
{
    keyValues.clear();
}

OneConfigCell OneConfigCell::operator=(const OneConfigCell &other)
{
    if(this != &other)
    {
        keyValues.clear();
        std::copy(other.keyValues.begin(), other.keyValues.end(), std::back_inserter(keyValues));
        if(other.innerCellPtr)
        {
            if(innerCellPtr == nullptr)
            {
                innerCellPtr = std::make_shared<OneConfigCell>();
            }
            *(innerCellPtr.get()) = *(other.innerCellPtr.get());
        }
        if(other.andConditionCellPtr)
        {
            if(andConditionCellPtr == nullptr)
            {
                andConditionCellPtr = std::make_shared<OneConfigCell>();
            }
            *(andConditionCellPtr.get()) = *(other.andConditionCellPtr.get());
        }
    }

    return *this;
}

//---------------------------------DESCRIPTOR CONFIG------------------------------------------

DescriptorConfig::DescriptorConfig()
{

}

DescriptorConfig::DescriptorConfig(const DescriptorConfig &other)
{
    std::copy(other.configFile.begin(), other.configFile.end(), std::back_inserter(configFile));
    this->parser = other.parser;
}

DescriptorConfig::~DescriptorConfig()
{
    configFile.clear();
}

std::vector<OneConfigCell> DescriptorConfig::getDescription(std::string configFilename)
{
    configFile.clear();

    parser = getJsonData(configFilename);
    std::vector<std::shared_ptr<JsonContainer>> configs = parser.findElementsByName("config");

    for(std::vector<std::shared_ptr<JsonContainer>>::iterator it = configs.begin(); it != configs.end(); it++)
    {
        std::shared_ptr<OneConfigCell> descriptedCellPtr = getFilledCell((*it)->childNode);
        OneConfigCell descriptedCellObj(*(descriptedCellPtr.get()));
        configFile.push_back(descriptedCellObj);
        descriptedCellPtr.reset();
    }

    return configFile;
}

std::shared_ptr<OneConfigCell> DescriptorConfig::getFilledCell(std::shared_ptr<JsonContainer> configContainer)
{
    std::shared_ptr<OneConfigCell> oneConfig = std::make_shared<OneConfigCell>();

    for(std::shared_ptr<JsonContainer> iterPtr = configContainer; iterPtr != nullptr; iterPtr = iterPtr->nextNode)
    {
        std::string key = iterPtr->keyValue.first;

        if((iterPtr->typeNode == json_space::STRING) && isValidKey(key))
        {
            std::string value = iterPtr->keyValue.second;
            oneConfig->keyValues.push_back(std::pair<std::string, std::string>(key, value));
        }
        else if((iterPtr->typeNode == json_space::OBJECT) && isValidKey(key))
        {
            if(key == INNER_CONDITION)
                oneConfig->innerCellPtr = getFilledCell(iterPtr->childNode);
            else
                oneConfig->andConditionCellPtr = getFilledCell(iterPtr->childNode);
        }
        else
        {
            // TO DO: Освободить ресурсы(удалить созданные объекты OneConfigCell, если они были созданы
            throw SIEM_errors::SIEMException("Incorrect node type in config file");
        }
    }

    return oneConfig;
}

bool DescriptorConfig::isValidKey(std::string key)
{
    if((key == TYPE_NODE)        ||
       (key == KEY_VALUE)        ||
       (key == PARAMETER_VALUE)  ||
       (key == HIGH_THRESHOLD)   ||
       (key == AND_CONDITION)    ||
       (key == INNER_CONDITION)  ||
       (key == CONFIG_PATH)      ||
       (key == TYPE_CONFIG))
    {
        return true;
    }
    return false;
}
