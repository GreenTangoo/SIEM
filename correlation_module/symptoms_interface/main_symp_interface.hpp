#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <string>
#include <vector>

#include "../all_categories.hpp"

namespace symptoms
{
    struct data
    {
        std::vector<std::string> main_data;
    };

    class Symptom_inter
    {
    public:
        Symptom_inter() = default;
        Symptom_inter(const Symptom_inter &other) = delete;
        Symptom_inter(Symptom_inter &&other) = default;
        std::vector<data> getData();
        virtual ~Symptom_inter() = default;
        virtual bool checkSymptoms() = 0;
    };
}

#endif
