#ifndef JSON_H
#define JSON_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>

namespace jsoner
{
    enum type_json_node {OBJECT, ARRAY, STRING, ROOT};

    class json_interface
    {
    protected:
        type_json_node node;
        std::list<std::pair<json_interface, json_interface>> json_node;
    public:
        explicit json_interface(type_json_node type_node);
        json_interface(const json_interface &other);
        ~json_interface();
        type_json_node getType();
        void add_nodes(json_interface one, json_interface two);
    };

    class json_object : public json_interface
    {
    public:
        explicit json_object(type_json_node type_node);
        json_object(const json_object &other);
        ~json_object();
    };

    class json_array : public json_interface
    {
    public:
        explicit json_array(type_json_node type_node);
        json_array(const json_array &other);
        ~json_array();
    };

    class json_string : public json_interface
    {
    private:
        std::string name;
    public:
        explicit json_string(std::string name_node);
        json_string(const json_string &other);
        ~json_string();
    };



    class json_parser
    {
    private:
        json_interface json_document;
    private:
        json_interface get_json_interface(std::istream &in);
        void getFromFile(std::istream &in);
        void putToFile(std::ostream &out);
    public:
        explicit json_parser();
        ~json_parser();
        void readJson(std::string filename);
        void writeJson(std::string filename);

        friend std::istream& operator>>(std::istream& fin, json_parser obj);
        friend std::ostream& operator<<(std::ostream& stream, json_parser obj);
    };
}
#endif
