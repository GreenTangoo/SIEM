#ifndef RECOGNITION_CATEGORIES_MAIN_H
#define RECOGNITION_CATEGORIES_MAIN_H

#include "recognition_interface.hpp"

using namespace symptoms_space;

namespace recognition_space
{
    class RecognitionCategory : public RecognitionInter
    {
    private:
        std::vector<SymptomImpl*> vectorSymptoms;
    public:
        RecognitionCategory();
        RecognitionCategory(SymptomImpl* obj);
        RecognitionCategory(std::vector<SymptomImpl*> vec_obj);
        ~RecognitionCategory();
        std::vector<SymptomImpl*> getAlertSymptoms();
        void addSymptomsChecker(std::vector<SymptomImpl*> obj);
    };
}

#endif // RECOGNITION_CATEGORIES_MAIN_H
