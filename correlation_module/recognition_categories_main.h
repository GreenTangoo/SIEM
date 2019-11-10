#ifndef RECOGNITION_CATEGORIES_MAIN_H
#define RECOGNITION_CATEGORIES_MAIN_H


#include <vector>

#include "recognition_interface.hpp"



using namespace symptoms;

namespace recognition
{
    class recognition_category : public recognition_inter
    {
    private:
        std::vector<symptoms::Symptom*> vector_symptoms;
    public:
        recognition_category();
        recognition_category(symptoms::Symptom* obj);
        recognition_category(std::vector<symptoms::Symptom*> vec_obj);
        ~recognition_category();
        std::vector<symptoms::Symptom*> getAlertSymptoms();
        void addSymptomChecker(symptoms::Symptom *obj);
    };
}

#endif // RECOGNITION_CATEGORIES_MAIN_H
