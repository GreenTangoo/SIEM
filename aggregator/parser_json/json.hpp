#ifndef JSON_H
#define JSON_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "../parser_txt/parser.hpp"

namespace jsoner
{
    enum type_cell {OBJECT = '}', ARRAY = ']', STRING, END_OBJECT = '{', END_ARRAY = '[', NONE};
    struct json_container
    {
        std::pair<std::string, std::string> one_cell;
        type_cell cell_type;

        json_container *next;
        json_container *prev;
        json_container *down;
        json_container *up;

        explicit json_container()
        {
            next = prev = down = up = nullptr;
            cell_type = NONE;
        }
        explicit json_container(type_cell celltype)
        {
            next = prev = down = up = nullptr;
            cell_type = celltype;
        }
        explicit json_container(std::string first_str, std::string second_str, type_cell celltype)
        {
            next = prev = down = up = nullptr;
            one_cell.first = first_str;
            one_cell.second = second_str;
            cell_type = celltype;
        }
        void setData(std::string first_str, std::string second_str, type_cell celltype)
        {
            one_cell.first = first_str;
            one_cell.second = second_str;
            cell_type = celltype;
        }
    };


    class json_parser
    {
    private:
        json_container *root;
    private:
        void erase_json_container(json_container **root);
        void add_child(json_container **node, json_container **new_container);
        void add_neighbord(json_container **node, json_container **new_container);
        json_container* find_element_by_name(json_container *node, std::string name);
        type_cell get_type(std::string source_str) const;
        void getFromStream(std::istream &in, json_container **node);
        void putToStream(std::ostream &out, json_container **node, int32_t offset);
        void copy_elements(json_container **node, const json_container *other);
        void delete_none_elements(json_container **node);
    public:
        json_parser();
        json_parser(const json_parser &other);
        json_parser(json_parser &&other);
        json_parser(json_container *other);
        ~json_parser();
        json_parser& operator=(const json_parser &other);
        void getJson(std::istream &input_stream);
        void setJson(std::ostream &output_stream);
        json_container* find_element_by_name(std::string name);
        std::list<json_container*> find_elements_by_name(std::string name);
    };

    static json_parser getJsonData(std::string filename)
    {
        std::ifstream fin;
        fin.open(filename.c_str());
        if(fin.is_open() == false)
            throw std::exception();

        json_parser return_parser;
        return_parser.getJson(fin);
        return return_parser;
    }
}
#endif
