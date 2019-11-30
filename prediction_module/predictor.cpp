#include "predictor.hpp"

analysis::prediction::prediction()
{

}

analysis::prediction::prediction(const topology::sub_graph &sub_graph_obj)
{
    analyseSubGraph(sub_graph_obj);
}

analysis::prediction::~prediction()
{

}

void analysis::prediction::analyseSubGraph(const topology::sub_graph &sub_graph_obj)
{
    std::ifstream fin;
    fin.open("vector_attacks.txt", std::ios_base::in);
    std::string input_str;

    while(std::getline(fin, input_str))
    {
        if(input_str[0] == '#')
            continue;

        long counter = 0;
        std::list<std::string> parsed_str = parser_string::parse_by_delimeter(input_str, "->");
        const std::vector<topology::symptom_info> all_info = sub_graph_obj.getSymptomInfo();
        for(size_t i(0); i < all_info.size(); i++)
        {
            if(category::getCategoryName(all_info[i].symp_type) == *(std::next(parsed_str.begin(), i)))
                counter++;
            else return;
        }

        for(std::list<std::string>::iterator it = std::next(parsed_str.begin(), counter); it != parsed_str.end(); it++)
            probably_later_categories.push_back(*it);
    }
}

std::vector<std::string> analysis::prediction::getProbablyLaterSymptoms()
{
    return probably_later_categories;
}
