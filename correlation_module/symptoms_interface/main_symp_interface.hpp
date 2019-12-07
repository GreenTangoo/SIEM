#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <vector>
#include <string>
#include <map>

#include "../all_categories.hpp"
#include "../../aggregator/time_class/parse_time.hpp"

namespace symptoms
{
    struct data
    {
        std::vector<std::pair<std::string, int16_t>> main_data;
        data_time::time time;
        bool is_used;
    };

    class Symptom_inter
    {
    public:
        Symptom_inter() = default;
        Symptom_inter(const Symptom_inter &other) = delete;
        Symptom_inter(Symptom_inter &&other) = default;
        virtual ~Symptom_inter() = default;
        virtual bool checkSymptoms() = 0;
    };
}

#endif
