#ifndef DISCOVERY_MAIN_HPP
#define DISCOVERY_MAIN_HPP

#include <vector>

#include "../recognition_interface.hpp"



using namespace symptoms;

namespace recognition
{
    class Discovery_symptoms_recognition : public recognition_inter
    {
    public:
        Discovery_symptoms_recognition();
        Discovery_symptoms_recognition(symptoms::Symptom* obj);
        Discovery_symptoms_recognition(std::vector<symptoms::Symptom*> vec_obj);
        ~Discovery_symptoms_recognition();
        std::vector<symptoms::Symptom*> getAlertSymptoms();
        void addSymptomChecker(symptoms::Symptom *obj);
        size_t getAmountFoundedSymptoms();
    };
}
#endif
