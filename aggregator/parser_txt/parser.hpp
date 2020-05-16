#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include <iostream>
#include <algorithm>

namespace parser_string_space
{
    enum symbolType {SPACE = ' ', DQUOTE = '\"', QUOTE = '\'', COMMA = ',', TAB = '\t', VERTICAL_SLASH = '|'};
    std::list<std::string> parse_by_delimeter(std::string sourceStr, std::string delimeter, bool parseOnce = false);
    std::string delete_symbol(std::string sourceStr, symbolType symbol);
}
#endif // PARSER_H
