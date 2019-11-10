#include "recognition_categories_main.h"



using namespace recognition;

recognition_category::recognition_category()
{

}

recognition_category::recognition_category(symptoms::Symptom* obj)
{
    vector_symptoms.push_back(obj);
}

recognition_category::recognition_category(std::vector<symptoms::Symptom*> vec_obj)
{
    vector_symptoms = vec_obj;
}

recognition_category::~recognition_category()
{
    for(size_t i(0); i < vector_symptoms.size(); i++)
        delete vector_symptoms[i];
}

std::vector<symptoms::Symptom *> recognition_category::getAlertSymptoms()
{
    std::vector<symptoms::Symptom*> recogh_symps;
    for(size_t i(0); i < vector_symptoms.size(); i++)
    {
        if(vector_symptoms[i]->checkSymptoms() == true)
            recogh_symps.push_back(vector_symptoms[i]);
    }

    return recogh_symps;
}

void recognition_category::addSymptomChecker(symptoms::Symptom *obj)
{
    vector_symptoms.push_back(obj);
}

