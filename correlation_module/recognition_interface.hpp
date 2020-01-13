#ifndef RECOGNITION_INTERFACE_HPP
#define RECOGNITION_INTERFACE_HPP

#include "symptoms_interface/symp_implementation.hpp"

namespace recognition
{
    class recognition_inter
    {
    public:
        recognition_inter() = default;
        virtual ~recognition_inter() = default;
        virtual std::vector<symptoms::Symptom_impl*> getAlertSymptoms() = 0;
        virtual void addSymptomsChecker(std::vector<symptoms::Symptom_impl*>obj) = 0;
    };
}

#endif
