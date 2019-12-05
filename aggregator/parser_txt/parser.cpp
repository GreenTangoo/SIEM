#include "parser.hpp"

namespace parser_string
{
    std::list<std::string> parse_by_delimeter(std::string source_str, std::string delimeter, bool parse_once)
    {
        std::list<std::string> return_list;
        size_t found = source_str.find(delimeter);
        size_t last_pos = 0;
        std::string temp;

        while(found != std::string::npos)
        {
            std::copy(source_str.begin() + last_pos, source_str.begin() + found, std::back_inserter(temp));
            return_list.push_back(temp);
            if(parse_once == true)
            {
                std::string second_part = source_str.substr(found + delimeter.size(), source_str.size() - temp.size() - delimeter.size());
                return_list.push_back(second_part);
                return return_list;
            }
            temp = "";
            last_pos = found + delimeter.size();
            found = source_str.find(delimeter, found + delimeter.size());
        }

        std::copy(source_str.begin() + last_pos, source_str.end(), std::back_inserter(temp));
        return_list.push_back(temp);

        return return_list;
    }

    std::string delete_symbol(std::string source_str, symbol_type symbol)
    {
        std::string return_str;
        for(size_t i(0); i < source_str.size(); i++)
            if(source_str[i] != symbol)
                return_str.push_back(source_str[i]);

        return return_str;
    }
}
