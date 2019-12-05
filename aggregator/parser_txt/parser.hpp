#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include <iostream>
#include <algorithm>

namespace parser_string
{
    enum symbol_type {SPACE = ' ', DQUOTE = '\"', QUOTE = '\'', COMMA = ',', TAB = '\t'};
    std::list<std::string> parse_by_delimeter(std::string source_str, std::string delimeter, bool parse_once = false);
    std::string delete_symbol(std::string source_str, symbol_type symbol);
}
#endif // PARSER_H
