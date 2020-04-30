#include "parser.hpp"

namespace parser_string_space
{
    std::list<std::string> parse_by_delimeter(std::string sourceStr, std::string delimeter, bool parseOnce)
    {
        std::list<std::string> returnList;
        size_t found = sourceStr.find(delimeter);
        size_t lastPos = 0;
        std::string temp;

        while(found != std::string::npos)
        {
            std::copy(sourceStr.begin() + lastPos, sourceStr.begin() + found, std::back_inserter(temp));
            returnList.push_back(temp);
            if(parseOnce == true)
            {
                std::string second_part = sourceStr.substr(found + delimeter.size(), sourceStr.size() - temp.size() - delimeter.size());
                returnList.push_back(second_part);
                return returnList;
            }
            temp = "";
            lastPos = found + delimeter.size();
            found = sourceStr.find(delimeter, found + delimeter.size());
        }

        std::copy(sourceStr.begin() + lastPos, sourceStr.end(), std::back_inserter(temp));
        returnList.push_back(temp);

        return returnList;
    }

    std::string delete_symbol(std::string sourceStr, symbolType symbol)
    {
        std::string returnStr;
        for(size_t i(0); i < sourceStr.size(); i++)
            if(sourceStr[i] != symbol)
                returnStr.push_back(sourceStr[i]);

        return returnStr;
    }
}
