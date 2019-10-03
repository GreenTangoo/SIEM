#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include <iostream>
#include <algorithm>

namespace parser_string
{
    std::list<std::string> parse_by_delimeter(std::string source_str, std::string delimeter);
}
#endif // PARSER_H
