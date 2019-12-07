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
    recognition_category *all_symptoms = new recognition_category();
    //all_symptoms->addSymptomsChecker(initializeDiscoveredSymptoms());
    all_symptoms->addSymptomsChecker(initializeAccountAccessSymptoms());
    //all_symptoms->addSymptomsChecker(initializeFilesManipulationSymptoms());
    //all_symptoms->addSymptomsChecker(initializeProccessManipulationSymptoms());

    initialized_vec = all_symptoms;
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
    std::vector<symptoms::Symptom_impl*> vec_alert_symptoms = initialized_vec->getAlertSymptoms();

    for(size_t i(0); i < vec_alert_symptoms.size(); i++)
    {
        for(size_t k(0); k < vec_alert_symptoms[i]->getData().size(); k++)
        {
            if(vec_alert_symptoms[i]->getData()[k].is_used == true)
                continue;

            std::vector<std::pair<std::string, int16_t>> passed_info = vec_alert_symptoms[i]->getData()[k].main_data;
            data_time::time passed_time = vec_alert_symptoms[i]->getData()[k].time;
            category::symptom_category passed_category = vec_alert_symptoms[i]->getSymptomType();

            sub_graph obj(passed_info, passed_category, passed_time);
            vec_alert_symptoms[i]->getData()[k].is_used = true;
            for(size_t j(0); j < vec_alert_symptoms.size(); j++)
            {
                if(i == j)
                    continue;
                obj.addSymptomInfo(vec_alert_symptoms[j]);
            }
            if(obj.getSymptomInfo().size() > 1)
                all_sub_graphs.push_back(obj);
        }
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
