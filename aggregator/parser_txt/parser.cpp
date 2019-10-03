#include "parser.hpp"

namespace parser_string
{
    std::list<std::string> parse_by_delimeter(std::string source_str, std::string delimeter)
    {
        std::list<std::string> return_list;
        size_t found = source_str.find(delimeter);
        size_t last_pos = 0;
        std::string temp;

        while(found != std::string::npos)
        {
            std::copy(source_str.begin() + last_pos, source_str.begin() + found, std::back_inserter(temp));
            return_list.push_back(temp);
            temp = "";
            last_pos = found + delimeter.size();
            found = source_str.find(delimeter, found + delimeter.size());
        }

        std::copy(source_str.begin() + last_pos, source_str.end(), std::back_inserter(temp));
        return_list.push_back(temp);

        return return_list;
    }
}
