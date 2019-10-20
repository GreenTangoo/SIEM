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
using namespace jsoner;

std::vector<symptoms::Symptom*> initialize_discovered_symptoms()
{
    std::vector<symptoms::Symptom*> vector_discovery_symptoms;
    PortScanningSymptoms *port_scan_symp = new PortScanningSymptoms("net_log.json");

    vector_discovery_symptoms.push_back(port_scan_symp);

    return vector_discovery_symptoms;
}

std::vector<recognition_inter*> initialize_recognitions_methods()
{
    std::vector<recognition_inter*> initialized_vec;

    Discovery_symptoms_recognition *all_discovery_symptoms = new Discovery_symptoms_recognition(initialize_discovered_symptoms());

    initialized_vec.push_back(all_discovery_symptoms);


    return initialized_vec;
}

int main()
{
    /*recognition::Discovery_symptoms_recognition obj;

    std::vector<recognition_inter*> vector_objs;
    vector_objs.push_back(&obj);

    for(size_t i(0); i < vector_objs.size(); i++)
    {
        if(typeid (*vector_objs[i]) == typeid (recognition::Discovery_symptoms_recognition))
            std::cout << "COMPARED" << std::endl;
    }*/

    std::vector<recognition_inter*> rec_main_vector = initialize_recognitions_methods();

    while(true)
    {
        for(size_t i(0); i < rec_main_vector.size(); i++)
        {
            std::vector<symptoms::Symptom*> symp_vector = rec_main_vector[i]->getAlertSymptoms();
            std::cout << symp_vector.size() << std::endl;
            for(size_t j(0); j < symp_vector.size(); j++)
                std::cout << symp_vector[j]->warning_msg() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
