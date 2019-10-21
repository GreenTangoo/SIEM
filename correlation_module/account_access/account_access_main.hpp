#ifndef ACCOUNT_ACCESS_MAIN_HPP
#define ACCOUNT_ACCESS_MAIN_HPP

#include <vector>

#include "../recognition_interface.hpp"

using namespace symptoms;

namespace recognition
{
    class Account_symptoms_recognition : public recognition_inter
    {
    private:
        std::vector<symptoms::Symptom*> vector_discovery_symptoms;
    public:
        Account_symptoms_recognition();
        Account_symptoms_recognition(symptoms::Symptom* obj);
        Account_symptoms_recognition(std::vector<symptoms::Symptom*> vec_obj);
        ~Account_symptoms_recognition();
        std::vector<symptoms::Symptom*> getAlertSymptoms();
        void addSymptomChecker(symptoms::Symptom *obj);
    };
}

#endif
