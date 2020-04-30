#include "sub_graph.h"

using namespace topology_space;

SubGraph::SubGraph()
{

}

SubGraph::SubGraph(std::vector<std::pair<std::string, int16_t>> info, category_space::symptomCategory sympCategrory, data_time_space::Time time)
{
    topology_space::SymptomInfo obj;
    obj.info = info;
    obj.sympType = sympCategrory;
    obj.time = time;

    signsVec.push_back(obj);
}

SubGraph::~SubGraph()
{

}

const std::vector<SymptomInfo> SubGraph::getSymptomInfo() const
{
    return signsVec;
}

void SubGraph::addSymptomInfo(symptoms_space::SymptomImpl *symp)
{
    std::vector<symptoms_space::Data> symptomData = symp->getData();
    /*Moving through the data from one symptom*/
    for(size_t i(0); i < symptomData.size(); i++)
    {
        std::vector<SymptomInfo> tempSignsVec = this->signsVec;
        /*Moving through the data from alredy added to sub_graph symptoms*/
        for(size_t j(0); j < this->signsVec.size(); j++)
        {
            std::vector<std::pair<std::string, int16_t>> outVec;

            std::sort(symptomData[i].mainData.begin(), symptomData[i].mainData.end(), [](const std::pair<std::string, int16_t> &obj1, const std::pair<std::string, int16_t> &obj2)
            {
                return obj1.first < obj2.first;
            });
            std::sort(this->signsVec[j].info.begin(), this->signsVec[j].info.end(), [](const std::pair<std::string, int16_t> &obj1, const std::pair<std::string, int16_t> &obj2)
            {
                return obj1.first < obj2.first;
            });

            /*Get data which contains in both vector(finding the relative signs between already added and othe symptoms)*/
            std::set_intersection(symptomData[i].mainData.begin(), symptomData[i].mainData.end(),
                    this->signsVec[j].info.begin(), this->signsVec[j].info.end(), std::back_inserter(outVec),
                      [](std::pair<std::string, int16_t> firstElem, std::pair<std::string, int16_t> secondElem) -> bool
            {
                if(firstElem.second == 0)
                    return true;
                if(firstElem.first < secondElem.first)
                    return true;
                else return false;
            });

            /*If founded more than one consilience*/
            if(outVec.size() > 0)
            {
                if(symp->getData()[i].isUsed == true)
                    continue;
                symp->getData()[i].isUsed = true;
                topology_space::SymptomInfo obj;
                obj.info = symptomData[i].mainData;
                obj.sympType = symp->getSymptomType();
                obj.time = symptomData[i].time;

                /*Checking for already added info from other symptom to vector inforamtion*/
                if(count_if(tempSignsVec.begin(), tempSignsVec.end(), [&obj](const SymptomInfo &sign_obj)
                {
                    return ((obj.sympType == sign_obj.sympType) && (obj.time == sign_obj.time));
                }) == 0)
                    tempSignsVec.push_back(obj);
                else std::cout << category_space::CategoryResolver::getInstance().getCategoryName(obj.sympType) << " " << obj.time.getStrTime() << std::endl;
            }
        }
        this->signsVec = tempSignsVec;
    }
}
