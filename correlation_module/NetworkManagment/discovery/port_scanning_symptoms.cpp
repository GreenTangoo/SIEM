#include "port_scanning_symptoms.hpp"

using namespace symptoms::discovery;


PortScanningSymptoms::PortScanningSymptoms(std::string filename) : json_filename(filename)
{
}

PortScanningSymptoms::~PortScanningSymptoms()
{

}

bool PortScanningSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("new_session");
    container = container->down;
    for(; container != nullptr; container = container->next)
    {
        if(atoi(container->down->one_cell.second.c_str()) > 100)
            return true;
    }
    return false;
}

std::string PortScanningSymptoms::warning_msg()
{
    return "Warning: port scan was recghonized";
}
