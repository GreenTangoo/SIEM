#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <vector>
#include <map>

#include "../all_categories.hpp"
#include "../../aggregator/time_class/parse_time.hpp"
#include "../../aggregator/parser_json/json.hpp"

namespace symptoms_space
{
    struct Data
    {
        std::vector<std::pair<std::string, int16_t>> mainData;
        data_time_space::Time time;
        bool isUsed;
    };

    class SymptomInter
    {
    public:
        SymptomInter() = default;
        SymptomInter(const SymptomInter &other) = delete;
        SymptomInter(SymptomInter &&other) = default;
        virtual ~SymptomInter() = default;
        virtual bool checkSymptoms() = 0;
    };
}

#endif
