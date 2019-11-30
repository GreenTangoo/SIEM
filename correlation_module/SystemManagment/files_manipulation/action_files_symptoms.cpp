#include "action_files_symptoms.hpp"

using namespace symptoms::files_manipulation;


ActionFilesSymptoms::ActionFilesSymptoms(std::string filename) : json_filename(filename)
{
    this->type_symp = category::symptom_category::action_files;
}

ActionFilesSymptoms::~ActionFilesSymptoms()
{

}

bool ActionFilesSymptoms::checkSymptoms()
{
    parser = jsoner::getJsonData(json_filename);

    jsoner::json_container *container = parser.find_element_by_name("users");
    container = container->down;
    for(; container != nullptr; container = container->next)
    {
        if(container->down->down->one_cell.second == "download")
        {
            symptoms::data data_obj;
            data_obj.main_data.push_back(container->one_cell.first);
            data_obj.main_data.push_back(container->down->one_cell.first);
            data_obj.main_data.push_back(container->down->down->one_cell.second);
            this->all_data_from_symptom.push_back(data_obj);
        }
    }
    if(this->all_data_from_symptom.size() > 0)
        return true;
    else return false;
}
