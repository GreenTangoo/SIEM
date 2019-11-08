#include "directory_discovery_symptoms.hpp"


using namespace symptoms::discovery;


DirectoryDiscoverySymptoms::DirectoryDiscoverySymptoms(std::string filename) : json_filename(filename)
{
}

DirectoryDiscoverySymptoms::~DirectoryDiscoverySymptoms()
{

}

bool DirectoryDiscoverySymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("request");
    container = container->down;

    for(; container != nullptr; container = container->next)
    {
        unsigned int amount_requests_from_one_ip = 0;
        jsoner::json_container *node_container = container->down->down;

        for(; node_container != nullptr; node_container = node_container->next)
            amount_requests_from_one_ip++;

        if(amount_requests_from_one_ip > 2)
            return true;
    }
    return false;
}

std::string DirectoryDiscoverySymptoms::warning_msg()
{
    return "Warning: directory traversal was recghonized";
}
