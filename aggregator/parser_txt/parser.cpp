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

            if(temp.length() > 0)
                returnList.push_back(temp);

            if(parseOnce == true)
            {
                std::string second_part = sourceStr.substr(found + delimeter.size(), sourceStr.size() - temp.size() - delimeter.size());
                if(second_part.length() > 0)
                {
                    returnList.push_back(second_part);
                    return returnList;
                }
            }
            temp = "";
            lastPos = found + delimeter.size();
            found = sourceStr.find(delimeter, found + delimeter.size());
        }

        std::copy(sourceStr.begin() + lastPos, sourceStr.end(), std::back_inserter(temp));
        if(temp.length() > 0)
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

    std::string cropFromEnd(std::string sourceStr, symbolType symbol)
    {
        std::string newStr = sourceStr;
        std::size_t cropIndex = std::numeric_limits<size_t>::max();

        for(size_t i(sourceStr.length() - 1); i != 0; i--)
        {
            if(sourceStr[i] == symbol)
            {
                cropIndex = i;
                break;
            }
        }

        if(cropIndex != std::numeric_limits<size_t>::max())
        {
            newStr.erase(cropIndex);
            return newStr;
        }

        return sourceStr;
    }

    std::string constructPath(symbolType symbol, int amountArgs, ...) // ... is a list of path construction elements
    {
        std::string pathString;
        pathString += symbol;

        va_list ap;
        va_start(ap, amountArgs);

        while(amountArgs--)
        {
            char *arg = va_arg(ap, char*);

            std::string pathElement(arg);
            pathString += pathElement;
            pathString += symbol;
        }
        va_end(ap);

        pathString.pop_back();
        return pathString;
    }
}
