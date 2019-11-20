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

    jsoner::json_container *container = parser.find_element_by_name("iptables");
    container = container->down;

    std::map<std::string, int32_t> ip_amount_req;
    for(; container != nullptr; container = container->next)
        ip_amount_req[container->one_cell.first]++;
    for(std::map<std::string, int32_t>::iterator it = ip_amount_req.begin(); it != ip_amount_req.end(); it++)
        if(it->second > 2)
        {
            symptoms::data user_data_obj;
            user_data_obj.main_data.push_back(it->first);
            this->data_from_all_symptoms.push_back(user_data_obj);
            return true;
        }
    return false;
}

std::string PortScanningSymptoms::warning_msg()
{
    return "Warning: port scan was recghonized";
}

std::vector<symptoms::data> PortScanningSymptoms::getData()
{
    return data_from_all_symptoms;
}
