#ifndef SYMP_IMPLEMENTATION_HPP
#define SYMP_IMPLEMENTATION_HPP

#include "main_symp_interface.hpp"

namespace symptoms
{
    class Symptom_impl : public Symptom_inter
    {
    protected:
        std::vector<data> all_data_from_symptom;
        category::symptom_category type_symp;
    public:
        Symptom_impl() = default;
        Symptom_impl(const Symptom_impl &other) = default;
        Symptom_impl(Symptom_impl &&other) = delete;
        ~Symptom_impl() = default;
        std::vector<data>& getData();
        category::symptom_category getSymptomType();
        virtual bool checkSymptoms() = 0;
    };
}

#endif
