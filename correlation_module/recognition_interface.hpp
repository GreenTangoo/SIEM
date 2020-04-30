#ifndef RECOGNITION_INTERFACE_HPP
#define RECOGNITION_INTERFACE_HPP

#include "symptoms_interface/symp_implementation.hpp"

namespace recognition_space
{
    class RecognitionInter
    {
    public:
        RecognitionInter() = default;
        virtual ~RecognitionInter() = default;
        virtual std::vector<symptoms_space::SymptomImpl*> getAlertSymptoms() = 0;
        virtual void addSymptomsChecker(std::vector<symptoms_space::SymptomImpl*>obj) = 0;
    };
}

#endif
