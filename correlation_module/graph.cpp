#include "graph.h"

using namespace topology;
using namespace recognition;

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
    recognition_category *all_files_manipulation_symptoms = new recognition_category(initializeFilesManipulationSymptoms());
    recognition_category *all_proccess_manipulation_symptoms = new recognition_category(initializeProccessManipulationSymptoms());

    initialized_vec.push_back(all_discovery_symptoms);
    initialized_vec.push_back(all_account_access_symptoms);
    initialized_vec.push_back(all_files_manipulation_symptoms);
    initialized_vec.push_back(all_proccess_manipulation_symptoms);
}

std::vector<symptoms::Symptom_impl*> graph::initializeDiscoveredSymptoms()
{
    std::vector<symptoms::Symptom_impl*> vector_discovery_symptoms;
    PortScanningSymptoms *port_scan_symp = new PortScanningSymptoms("net_log.json");
    DirectoryDiscoverySymptoms *dir_scan_symp = new DirectoryDiscoverySymptoms("apache2.json");

    vector_discovery_symptoms.push_back(port_scan_symp);
    vector_discovery_symptoms.push_back(dir_scan_symp);

    return vector_discovery_symptoms;
}

std::vector<symptoms::Symptom_impl*> graph::initializeAccountAccessSymptoms()
{
    std::vector<symptoms::Symptom_impl*> vector_account_symptoms;
    UserLoginSymptoms *usr_log_symp = new UserLoginSymptoms("auth.json");
    LoginRootSymptoms *log_root_symp = new LoginRootSymptoms("auth.json");

    vector_account_symptoms.push_back(usr_log_symp);
    vector_account_symptoms.push_back(log_root_symp);

    return vector_account_symptoms;
}

std::vector<symptoms::Symptom_impl*> graph::initializeFilesManipulationSymptoms()
{
    std::vector<symptoms::Symptom_impl*> vector_files_manipulation_symptoms;
    ActionFilesSymptoms *action_files_symp = new ActionFilesSymptoms("system_files.json");

    vector_files_manipulation_symptoms.push_back(action_files_symp);

    return vector_files_manipulation_symptoms;
}

std::vector<Symptom_impl*> graph::initializeProccessManipulationSymptoms()
{
    std::vector<symptoms::Symptom_impl*> vector_proccess_manipulation_symptoms;
    ActionProccessSymptoms *action_proccess_symp = new ActionProccessSymptoms("system_proccesses.json");

    vector_proccess_manipulation_symptoms.push_back(action_proccess_symp);

    return vector_proccess_manipulation_symptoms;
}


void graph::fillGraph()
{
    for(size_t i(0); i < 1; i++)
    {
        std::vector<symptoms::Symptom_impl*> vec_alert_symptoms = initialized_vec[0]->getAlertSymptoms();

        for(size_t j(0); j < vec_alert_symptoms.size(); j++)
        {
            for(size_t k(0); k < vec_alert_symptoms[j]->getData().size(); k++)
            {
                std::vector<std::string> symptom_data = vec_alert_symptoms[j]->getData()[k].main_data;
                sub_graph sub_graph_obj;
                sub_graph_obj.addSymptomInfo(symptom_data, vec_alert_symptoms[j]->getSymptomType());
                getOneAttackVector(i + 1, sub_graph_obj);
                all_sub_graphs.push_back(sub_graph_obj);
            }
        }
    }
    crop_unsuspicious_sub_graphs();
}

void graph::getOneAttackVector(size_t curr_index, sub_graph &obj)
{
    if(curr_index >= initialized_vec.size())
        return;

    std::vector<symptoms::Symptom_impl*> alert_vec = initialized_vec[curr_index]->getAlertSymptoms();

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
                        obj.addSymptomInfo(symp_data[j].main_data, alert_vec[i]->getSymptomType());
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

void graph::crop_unsuspicious_sub_graphs()
{
    std::list<sub_graph> croped_graphs;
    for(std::list<sub_graph>::iterator it = all_sub_graphs.begin(); it != all_sub_graphs.end(); it++)
    {
        std::vector<symptom_info> info = it->getSymptomInfo();
        if(info.size() > 2)
            croped_graphs.push_back(*it);
    }
    all_sub_graphs = croped_graphs;
}

std::list<sub_graph> graph::getAllSubGraphs()
{
    return all_sub_graphs;
}
