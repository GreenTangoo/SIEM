#include "graph.h"
#include "../logfile_defines.hpp"

using namespace topology_space;
using namespace recognition_space;

Graph::Graph()
{

}

Graph::~Graph()
{

}


void Graph::initializeRecognitionMethods()
{
    RecognitionCategory *all_symptoms = new RecognitionCategory();
    all_symptoms->addSymptomsChecker(initializeDiscoveredSymptoms());
    all_symptoms->addSymptomsChecker(initializeAccountAccessSymptoms());
    all_symptoms->addSymptomsChecker(initializeFilesManipulationSymptoms());
    all_symptoms->addSymptomsChecker(initializeProccessManipulationSymptoms());
    all_symptoms->addSymptomsChecker(initializeCustomSymptoms());

    initializedVec = all_symptoms;
}

std::vector<symptoms_space::SymptomImpl*> Graph::initializeCustomSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> vectorCustomSymtoms;
    DescriptorConfig userConfigDescriptor;

    std::vector<OneConfigCell> configs = userConfigDescriptor.getDescription(CORRELATION_CONF_PATH);

    for(size_t i(0); i < configs.size(); i++)
    {
        CustomSymptoms *customSymp = new CustomSymptoms(configs[i]);
        vectorCustomSymtoms.push_back(customSymp);
    }

    return vectorCustomSymtoms;
}

std::vector<symptoms_space::SymptomImpl*> Graph::initializeDiscoveredSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> vector_discovery_symptoms;
    PortScanningSymptoms *port_scan_symp = new PortScanningSymptoms(IPTABLES_LOG_PATH);
    DirectoryDiscoverySymptoms *dir_scan_symp = new DirectoryDiscoverySymptoms(APACHE_LOG_PATH);

    vector_discovery_symptoms.push_back(port_scan_symp);
    vector_discovery_symptoms.push_back(dir_scan_symp);

    return vector_discovery_symptoms;
}

std::vector<symptoms_space::SymptomImpl*> Graph::initializeAccountAccessSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> vector_account_symptoms;
    UserLoginSymptoms *usr_log_symp = new UserLoginSymptoms(SYSTEM_AUTHORIZATION_LOG_PATH);
    LoginRootSymptoms *log_root_symp = new LoginRootSymptoms(SYSTEM_AUTHORIZATION_LOG_PATH);
    ValidAccountsSymptoms *validAccountsSympPtr = new ValidAccountsSymptoms(SYSTEM_AUTHORIZATION_LOG_PATH);

    vector_account_symptoms.push_back(usr_log_symp);
    vector_account_symptoms.push_back(log_root_symp);
    vector_account_symptoms.push_back(validAccountsSympPtr);

    return vector_account_symptoms;
}

std::vector<symptoms_space::SymptomImpl*> Graph::initializeFilesManipulationSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> vector_files_manipulation_symptoms;
    DataCollectionSymptoms *data_collection_symp = new DataCollectionSymptoms(SYSTEM_FILES_MANIPULATION_LOG_PATH);
    AccountDiscoverySymptoms *account_discovery_symp = new AccountDiscoverySymptoms(SYSTEM_FILES_MANIPULATION_LOG_PATH);

    vector_files_manipulation_symptoms.push_back(data_collection_symp);
    vector_files_manipulation_symptoms.push_back(account_discovery_symp);

    return vector_files_manipulation_symptoms;
}

std::vector<SymptomImpl*> Graph::initializeProccessManipulationSymptoms()
{
    std::vector<symptoms_space::SymptomImpl*> vector_proccess_manipulation_symptoms;
    ProcessDiscoverySymptoms *process_discovery_symp = new ProcessDiscoverySymptoms(SYSTEM_PROCESSES_MANIPULATION_LOG_PATH);
    CommandLineInterfaceSymptoms *cmd_symptoms = new CommandLineInterfaceSymptoms(SYSTEM_PROCESSES_MANIPULATION_LOG_PATH);
    DataCompressedSymptoms *data_compressed_symp = new DataCompressedSymptoms(SYSTEM_PROCESSES_MANIPULATION_LOG_PATH);
    SystemNetworkConfDiscoverySymptoms *net_conf_discovery_symp = new SystemNetworkConfDiscoverySymptoms(SYSTEM_PROCESSES_MANIPULATION_LOG_PATH);
    SystemNetworkConnDiscoverySymptoms *net_conn_discovery_symp = new SystemNetworkConnDiscoverySymptoms(SYSTEM_PROCESSES_MANIPULATION_LOG_PATH);

    vector_proccess_manipulation_symptoms.push_back(process_discovery_symp);
    vector_proccess_manipulation_symptoms.push_back(cmd_symptoms);
    vector_proccess_manipulation_symptoms.push_back(data_compressed_symp);
    vector_proccess_manipulation_symptoms.push_back(net_conf_discovery_symp);
    vector_proccess_manipulation_symptoms.push_back(net_conn_discovery_symp);

    return vector_proccess_manipulation_symptoms;
}

/*This method run along through the symptoms and contructs the sub_graph of relative syptoms by signs*/
void Graph::fillGraph()
{
    std::vector<symptoms_space::SymptomImpl*> vec_alert_symptoms = initializedVec->getAlertSymptoms();

    /*Moving through the all alert symptoms for get info from all of them*/
    for(size_t i(0); i < vec_alert_symptoms.size(); i++)
    {
        /*Moving through the vector information from each symptom*/
        for(size_t k(0); k < vec_alert_symptoms[i]->getData().size(); k++)
        {
            if(vec_alert_symptoms[i]->getData()[k].isUsed == true)
                continue;

            /*Get information about one symptom(one sign from symptom)*/
            std::vector<std::pair<std::string, int16_t>> passed_info = vec_alert_symptoms[i]->getData()[k].mainData;
            data_time_space::Time passed_time = vec_alert_symptoms[i]->getData()[k].time;
            category_space::symptomCategory passed_category = vec_alert_symptoms[i]->getSymptomType();

            /*Creating a new sub_graph object and filling his first data of the first symptom*/
            SubGraph obj(passed_info, passed_category, passed_time);
            vec_alert_symptoms[i]->getData()[k].isUsed = true;
            /*Moving through the other symptoms to check each of them for having relative signs*/
            for(size_t j(0); j < vec_alert_symptoms.size(); j++)
            {
                if(i == j)
                    continue;
                obj.addSymptomInfo(vec_alert_symptoms[j]); // Add information about other symptom if founds relative signs
            }
            if(obj.getSymptomInfo().size() > 1) // If founded more than two events IS
                allSubGraphs.push_back(obj);
        }
    }
}

void Graph::crop_unsuspicious_sub_graphs()
{
    std::list<SubGraph> croped_graphs;
    for(std::list<SubGraph>::iterator it = allSubGraphs.begin(); it != allSubGraphs.end(); it++)
    {
        std::vector<SymptomInfo> info = it->getSymptomInfo();
        if(info.size() > 2)
            croped_graphs.push_back(*it);
    }
    allSubGraphs = croped_graphs;
}

std::list<SubGraph> Graph::getAllSubGraphs()
{
    return allSubGraphs;
}
