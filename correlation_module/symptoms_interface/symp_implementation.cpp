#include "symp_implementation.hpp"

std::vector<symptoms::data>& symptoms::Symptom_impl::getData()
{
    return all_data_from_symptom;
}

category::symptom_category symptoms::Symptom_impl::getSymptomType()
{
    return type_symp;
}
