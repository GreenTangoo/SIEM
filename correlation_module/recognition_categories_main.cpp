#include "recognition_categories_main.h"



using namespace recognition_space;

RecognitionCategory::RecognitionCategory()
{

}

RecognitionCategory::RecognitionCategory(symptoms_space::SymptomImpl* obj)
{
    vectorSymptoms.push_back(obj);
}

RecognitionCategory::RecognitionCategory(std::vector<symptoms_space::SymptomImpl*> vecObj)
{
    vectorSymptoms = vecObj;
}

RecognitionCategory::~RecognitionCategory()
{
    for(size_t i(0); i < vectorSymptoms.size(); i++)
        delete vectorSymptoms[i];
}

/*This method returns vector of alert symptoms(symptoms which signs was reghonized)*/
std::vector<symptoms_space::SymptomImpl*> RecognitionCategory::getAlertSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> recoghSymps;
    for(size_t i(0); i < vectorSymptoms.size(); i++)
    {
        if(vectorSymptoms[i]->checkSymptoms() == true)
            recoghSymps.push_back(vectorSymptoms[i]);
    }

    return recoghSymps;
}

/*Add a new symptom to checking symptoms vector*/
void RecognitionCategory::addSymptomsChecker(std::vector<symptoms_space::SymptomImpl*>obj)
{
    vectorSymptoms.insert(vectorSymptoms.end(), obj.begin(), obj.end());
}

