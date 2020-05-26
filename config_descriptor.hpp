#ifndef CONFIG_DESCRIPTOR
#define CONFIG_DESCRIPTOR

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

#include "aggregator/parser_json/json.hpp"
#include "correlation_module/all_categories.hpp"

#define CONFIG_PATH "config-path"
#define TYPE_CONFIG "type-config"
#define TYPE_NODE "type-node"
#define KEY_VALUE "key-value"
#define PARAMETER_VALUE "parameter-value"
#define HIGH_THRESHOLD "high-threshold"
#define AND_CONDITION "and-condition"
#define INNER_CONDITION "inner-condition"

using namespace json_space;

namespace config_space
{
    struct OneConfigCell
    {
        std::vector<std::pair<std::string, std::string>> keyValues;
        std::shared_ptr<OneConfigCell> innerCellPtr;
        std::shared_ptr<OneConfigCell> andConditionCellPtr;

        OneConfigCell();
        OneConfigCell(const OneConfigCell &other);
        OneConfigCell(OneConfigCell &&other);
        ~OneConfigCell();
        OneConfigCell operator=(const OneConfigCell &other);
    };

    class DescriptorConfig
    {
    private:
        std::vector<OneConfigCell> configFile;
        json_space::JsonObject parser;
    private:
        std::shared_ptr<OneConfigCell> getFilledCell(std::shared_ptr<JsonContainer> configContainer);
        bool isValidKey(std::string key);
    public:
        DescriptorConfig();
        DescriptorConfig(const DescriptorConfig &other);
        ~DescriptorConfig();
        std::vector<OneConfigCell> getDescription(std::string configFilename);
    };
}

#endif // CONFIG_DESCRIPTOR
