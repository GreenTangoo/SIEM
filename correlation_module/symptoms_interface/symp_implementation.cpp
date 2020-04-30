#include "symp_implementation.hpp"

std::vector<symptoms_space::Data>& symptoms_space::SymptomImpl::getData()
{
    return allDataFromSymptom;
}

category_space::symptomCategory symptoms_space::SymptomImpl::getSymptomType()
{
    return typeSymp;
}
