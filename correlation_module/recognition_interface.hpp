#ifndef RECOGNITION_INTERFACE_HPP
#define RECOGNITION_INTERFACE_HPP

#include <vector>

#include "symptoms_interface/main_symp_interface.hpp"

namespace recognition
{
    class recognition_inter
    {
    protected:
        std::vector<symptoms::Symptom*> vector_symptoms;
    public:
        recognition_inter() = default;
        virtual ~recognition_inter() = default;
        virtual std::vector<symptoms::Symptom*> getAlertSymptoms() = 0;
        virtual void addSymptomChecker(symptoms::Symptom *obj) = 0;
        virtual size_t getAmountFoundedSymptoms() = 0;
    };
}

#endif
