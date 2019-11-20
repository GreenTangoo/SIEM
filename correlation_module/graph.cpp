#include "graph.h"

using namespace topology;
using namespace recognition;
using namespace symptoms::discovery;
using namespace symptoms::account_access;

graph::graph()
{

}

graph::~graph()
{

}

void graph::initializeRecognitionMethods()
{
    recognition_category *all_discovery_symptoms = new recognition_category(initializeDiscoveredSymptoms());
    recognition_category *all_account_access_symptoms = new recognition_category(initializeAccountAccessSymptoms());
    initialized_vec.push_back(all_discovery_symptoms);
    initialized_vec.push_back(all_account_access_symptoms);
}

std::vector<symptoms::Symptom*> graph::initializeDiscoveredSymptoms()
{
    std::vector<symptoms::Symptom*> vector_discovery_symptoms;
    PortScanningSymptoms *port_scan_symp = new PortScanningSymptoms("net_log.json");
    DirectoryDiscoverySymptoms *dir_scan_symp = new DirectoryDiscoverySymptoms("apache2.json");

    vector_discovery_symptoms.push_back(port_scan_symp);
    vector_discovery_symptoms.push_back(dir_scan_symp);

    return vector_discovery_symptoms;
}

std::vector<symptoms::Symptom*> graph::initializeAccountAccessSymptoms()
{
    std::vector<symptoms::Symptom*> vector_account_symptoms;
    UserLoginSymptoms *usr_log_symp = new UserLoginSymptoms("auth.json");

    vector_account_symptoms.push_back(usr_log_symp);

    return vector_account_symptoms;
}

void graph::fillGraph()
{
    std::vector<symptoms::Symptom*> vec_alert_symptoms = initialized_vec[0]->getAlertSymptoms();

    for(size_t i(0); i < vec_alert_symptoms.size(); i++)
    {
        sub_graph sub_graph_obj;
        sub_graph_obj.addSymptomInfo(vec_alert_symptoms[i]->getData()[0].main_data);
        getOneAttackVector(1, sub_graph_obj);
        all_sub_graphs.push_back(sub_graph_obj);
    }
}

void graph::getOneAttackVector(size_t curr_index, sub_graph &obj)
{
    if(curr_index >= initialized_vec.size())
        return;

    std::vector<symptoms::Symptom*> alert_vec = initialized_vec[curr_index]->getAlertSymptoms();

    std::vector<symptom_info> get_founded_symp = obj.getSymptomInfo();

    bool is_founded = false;
    for(size_t i(0); i < alert_vec.size(); i++)
    {
        std::vector<data> symp_data = alert_vec[i]->getData();
        for(size_t j(0); j < symp_data.size(); j++)
        {
            for(size_t k(0); k < get_founded_symp.size(); k++)
            {
                for(size_t z(0); z < get_founded_symp[k].vec_info.size(); z++)
                {
                    if(std::count(symp_data[j].main_data.begin(), symp_data[j].main_data.end(), get_founded_symp[k].vec_info[z]) != 0)
                    {
                        is_founded = true;
                        obj.addSymptomInfo(symp_data[j].main_data);
                        getOneAttackVector(++curr_index, obj);
                        break;
                    }
                }
                if(is_founded == true)
                    break;
            }
            if(is_founded == true)
                break;
        }
        if(is_founded == true)
            break;
    }
}

std::vector<sub_graph> graph::getAllSubGraphs()
{
    return all_sub_graphs;
}
