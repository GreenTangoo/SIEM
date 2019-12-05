#include "recognition_categories_main.h"



using namespace recognition;

recognition_category::recognition_category()
{

}

recognition_category::recognition_category(symptoms::Symptom_impl* obj)
{
    vector_symptoms.push_back(obj);
}

recognition_category::recognition_category(std::vector<symptoms::Symptom_impl*> vec_obj)
{
    vector_symptoms = vec_obj;
}

recognition_category::~recognition_category()
{
    for(size_t i(0); i < vector_symptoms.size(); i++)
        delete vector_symptoms[i];
}

std::vector<symptoms::Symptom_impl*> recognition_category::getAlertSymptoms()
{
    std::vector<symptoms::Symptom_impl*> recogh_symps;
    for(size_t i(0); i < vector_symptoms.size(); i++)
    {
        if(vector_symptoms[i]->checkSymptoms() == true)
            recogh_symps.push_back(vector_symptoms[i]);
    }

    return recogh_symps;
}

void recognition_category::addSymptomsChecker(std::vector<symptoms::Symptom_impl*>obj)
{
    vector_symptoms.insert(vector_symptoms.end(), obj.begin(), obj.end());
}

