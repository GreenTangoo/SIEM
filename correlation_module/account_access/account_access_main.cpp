#include "account_access_main.hpp"

using namespace recognition;

Account_symptoms_recognition::Account_symptoms_recognition()
{

}

Account_symptoms_recognition::Account_symptoms_recognition(symptoms::Symptom* obj)
{
    vector_discovery_symptoms.push_back(obj);
}

Account_symptoms_recognition::Account_symptoms_recognition(std::vector<symptoms::Symptom*> vec_obj)
{
    vector_discovery_symptoms = vec_obj;
}

Account_symptoms_recognition::~Account_symptoms_recognition()
{
    for(size_t i(0); i < vector_discovery_symptoms.size(); i++)
        delete vector_discovery_symptoms[i];
}

std::vector<symptoms::Symptom *> Account_symptoms_recognition::getAlertSymptoms()
{
    std::vector<symptoms::Symptom*> recogh_symps;
    for(size_t i(0); i < vector_discovery_symptoms.size(); i++)
    {
        if(vector_discovery_symptoms[i]->checkSymptoms() == true)
            recogh_symps.push_back(vector_discovery_symptoms[i]);
    }

    return recogh_symps;
}

void Account_symptoms_recognition::addSymptomChecker(symptoms::Symptom *obj)
{
    vector_discovery_symptoms.push_back(obj);
}
