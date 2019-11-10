#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "aggregator/parser_json/json.hpp"
#include "aggregator/parser_txt/parser.hpp"

#include "correlation_module/all_symptoms.hpp"

using namespace recognition;
using namespace symptoms::discovery;
using namespace symptoms::account_access;
using namespace jsoner;

std::vector<symptoms::Symptom*> initialize_discovered_symptoms()
{
    std::vector<symptoms::Symptom*> vector_discovery_symptoms;
    PortScanningSymptoms *port_scan_symp = new PortScanningSymptoms("net_log.json");
    DirectoryDiscoverySymptoms *dir_scan_symp = new DirectoryDiscoverySymptoms("apache2.json");

    vector_discovery_symptoms.push_back(port_scan_symp);
    vector_discovery_symptoms.push_back(dir_scan_symp);

    return vector_discovery_symptoms;
}

std::vector<symptoms::Symptom*> initialize_account_access_symptoms()
{
    std::vector<symptoms::Symptom*> vector_account_symptoms;
    UserLoginSymptoms *usr_log_symp = new UserLoginSymptoms("auth.json");

    vector_account_symptoms.push_back(usr_log_symp);

    return vector_account_symptoms;
}

std::vector<recognition_inter*> initialize_recognitions_methods()
{
    std::vector<recognition_inter*> initialized_vec;

    recognition_category *all_discovery_symptoms = new recognition_category(initialize_discovered_symptoms());
    recognition_category *all_account_access_symptoms = new recognition_category(initialize_account_access_symptoms());
    initialized_vec.push_back(all_discovery_symptoms);
    initialized_vec.push_back(all_account_access_symptoms);

    return initialized_vec;
}

void reportAbouSymptoms(const std::vector<recognition_inter*> &rec_vector)
{
    for(size_t i(0); i < rec_vector.size(); i++)
    {
        std::vector<symptoms::Symptom*> symp_vector = rec_vector[i]->getAlertSymptoms();
        for(size_t j(0); j < symp_vector.size(); j++)
            std::cout << symp_vector[j]->warning_msg() << std::endl;
    }
}

int main()
{
    std::vector<recognition_inter*> rec_main_vector = initialize_recognitions_methods();

    while(true)
    {

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}
