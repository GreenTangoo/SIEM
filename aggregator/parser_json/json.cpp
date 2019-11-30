#include "json.hpp"


using namespace jsoner;

json_parser::json_parser()
{
    root = new json_container(OBJECT);
}

json_parser::json_parser(const json_parser &other)
{
    root = new json_container(OBJECT);
    json_container *child = new json_container;
    add_child(&root, &child);
    copy_elements(&root, other.root);
    delete_none_elements(&root);
}

json_parser::json_parser(json_parser &&other)
{
    this->root = other.root;
    other.root = nullptr;
}

json_parser::json_parser(json_container *other)
{
    root = new json_container(OBJECT);
    json_container *child = new json_container;
    add_child(&root, &child);
    copy_elements(&(root->down), other);
    delete_none_elements(&root);
}

json_parser::~json_parser()
{
    erase_json_container(&root);
}

json_parser& json_parser::operator=(const json_parser &other)
{
    if(this != &other)
    {
        this->erase_json_container(&root);
        root = new json_container(OBJECT);
        json_container *child = new json_container;
        add_child(&root, &child);
        copy_elements(&(root->down), other.root);
        delete_none_elements(&root);
    }
    return *this;
}

type_cell json_parser::get_type(std::string source_str) const
{
    if(source_str == "{")
        return OBJECT;
    if(source_str == "}")
        return END_OBJECT;
    if(source_str == "[")
        return ARRAY;
    if(source_str == "]")
        return END_ARRAY;

    return STRING;
}

void json_parser::erase_json_container(json_container **root)
{
    /*json_container *temp = *root;

    if(temp->down != nullptr)
        erase_json_container(&temp->down);
    if(temp->next != nullptr)
        erase_json_container(&temp->next);

    if((temp->next == nullptr) && (temp->down == nullptr))
    {
        delete temp;
        temp = nullptr;
        return;
    }*/
}

void json_parser::add_child(json_container **node, json_container **new_container)
{
    json_container *temp = *node;
    temp->down = *new_container;
    (*new_container)->up = temp;
}

void json_parser::add_neighbord(json_container **node, json_container **new_container)
{
    json_container *temp = *node;
    temp->next = *new_container;
    (*new_container)->prev = temp;
    (*new_container)->up = temp->up;
}

void json_parser::getFromStream(std::istream &in, json_container **node)
{
    json_container *temp_node = *node;
    std::string input_str;
    std::string first_part_str;
    std::string second_part_str;
    while(std::getline(in, input_str))
    {
        std::list<std::string> parsed = parser_string::parse_by_delimeter(input_str, ":");
        if(parsed.size() > 1)
        {
            std::list<std::string>::iterator it = std::next(parsed.begin(), 0);
            first_part_str = *it;
            it = std::next(parsed.begin(), 1);
            second_part_str = *it;

            first_part_str = parser_string::delete_symbol(first_part_str, parser_string::TAB);
            first_part_str = parser_string::delete_symbol(first_part_str, parser_string::COMMA);
            first_part_str = parser_string::delete_symbol(first_part_str, parser_string::DQUOTE);
            first_part_str = parser_string::delete_symbol(first_part_str, parser_string::SPACE);
        }
        else
        {
            first_part_str = "";
            std::list<std::string>::iterator it = std::next(parsed.begin(), 0);
            second_part_str = *it;
        }

        second_part_str = parser_string::delete_symbol(second_part_str, parser_string::TAB);
        second_part_str = parser_string::delete_symbol(second_part_str, parser_string::COMMA);
        second_part_str = parser_string::delete_symbol(second_part_str, parser_string::DQUOTE);
        second_part_str = parser_string::delete_symbol(second_part_str, parser_string::SPACE);

        type_cell type = get_type(parser_string::delete_symbol(second_part_str, parser_string::SPACE));
        if((type == END_ARRAY) || (type == END_OBJECT))
        {
            /*temp_node->prev->next = nullptr;
            delete temp_node;*/
            return;
        }

        temp_node->setData(first_part_str, second_part_str, type);

        if((type == OBJECT) || (type == ARRAY))
        {
            json_container *temp = new json_container;
            add_child(&temp_node, &temp);
            getFromStream(in, &(temp_node->down));
        }
        json_container *temp = new json_container;
        add_neighbord(&temp_node, &temp);
        temp_node = temp_node->next;
        /*if(type == STRING)
        {
            json_container *temp = new json_container;
            add_neighbord(&temp_node, &temp);
            temp_node = temp_node->next;
        }*/
    }
}

void json_parser::putToStream(std::ostream &out, json_container **node, int32_t offset)
{
    json_container *temp = *node;
    std::string out_str;
    while(true)
    {
        if((temp->cell_type == OBJECT) || (temp->cell_type == ARRAY))
        {
            out_str = std::string("\t", offset) + temp->one_cell.first + " : " + temp->one_cell.second + "\n";
            if(temp->one_cell.first != "")
                out.write(out_str.c_str(), out_str.size());
            else out.write(std::string(temp->one_cell.second + "\n").c_str(), temp->one_cell.second.size() + 1);
            putToStream(out, &(temp->down), offset + 1);
        }
        if(temp->cell_type == STRING)
        {
            out_str = std::string("\t", offset) + temp->one_cell.first + " : " + temp->one_cell.second + ",\n";
            out.write(out_str.c_str(), out_str.size());
        }
        if(temp->next == nullptr)
            break;
        temp = temp->next;
    }
    if((temp->up->cell_type == OBJECT) || (temp->up->cell_type == ARRAY))
    {
        if(temp->up->next != nullptr)
        {
            out_str.clear();
            out_str.push_back(static_cast<char>(temp->up->cell_type));
            out_str.push_back('\n');
            out.write(out_str.c_str(), out_str.size());
        }
        else
        {
            out_str.clear();
            out_str.push_back(static_cast<char>(temp->up->cell_type));
            out_str.push_back('\n');
            out.write(out_str.c_str(), out_str.size());
        }
    }
}

void json_parser::copy_elements(json_container **node, const json_container *other)
{
    json_container *temp_node = *node;
    const json_container *temp_other = other;

    if(temp_other->cell_type == NONE)
        copy_elements(&temp_node, temp_other->down);

    for(; temp_other != nullptr; temp_other = temp_other->next)
    {
        temp_node->setData(temp_other->one_cell.first, temp_other->one_cell.second, temp_other->cell_type);

        if((temp_other->cell_type == OBJECT) || (temp_other->cell_type == ARRAY))
        {
            json_container *temp = new json_container;
            add_child(&temp_node, &temp);
            copy_elements(&(temp_node->down), temp_other->down);
        }
        json_container *temp = new json_container;
        add_neighbord(&temp_node, &temp);
        temp_node = temp_node->next;
    }
}

void json_parser::delete_none_elements(json_container **node)
{
    json_container *temp = *node;

    for(;;)
    {
        if(temp->down != nullptr)
            delete_none_elements(&(temp->down));
        if(temp->next == nullptr)
            break;
        temp = temp->next;
    }
    while(temp->cell_type == NONE)
    {
        json_container *prev = temp->prev;
        delete temp;
        temp = prev;
        temp->next = nullptr;
    }
}

void json_parser::getJson(std::istream &input_stream)
{
    erase_json_container(&root);
    root = new json_container(OBJECT);
    getFromStream(input_stream, &root);
    delete_none_elements(&root);
}

void json_parser::setJson(std::ostream &output_stream)
{
    putToStream(output_stream, &root, 0);
}

json_container* json_parser::find_element_by_name(std::string name)
{
    return this->find_element_by_name(root, name);
}

json_container* json_parser::find_element_by_name(json_container *node, std::string name)
{
    json_container *temp = node;
    for(; temp != nullptr; temp = temp->next)
    {
        if(temp->one_cell.first == name)
            return temp;
        if(temp->cell_type != STRING)
        {
            json_container *return_type = find_element_by_name(temp->down, name);
            if(return_type != nullptr)
                return return_type;
        }
    }
    return nullptr;
}

std::list<json_container*> json_parser::find_elements_by_name(std::string name)
{

}
