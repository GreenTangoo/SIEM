#ifndef SYMP_IMPLEMENTATION_HPP
#define SYMP_IMPLEMENTATION_HPP

#include "main_symp_interface.hpp"

namespace symptoms_space
{
    class SymptomImpl : public SymptomInter
    {
    protected:
        std::vector<Data> allDataFromSymptom;
        category_space::symptomCategory typeSymp;
    public:
        SymptomImpl() = default;
        SymptomImpl(const SymptomImpl &other) = default;
        SymptomImpl(SymptomImpl &&other) = delete;
        ~SymptomImpl() = default;
        std::vector<Data>& getData();
        category_space::symptomCategory getSymptomType();
        virtual bool checkSymptoms() = 0;
    };
}

#endif
