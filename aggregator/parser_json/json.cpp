#include "json.hpp"

using namespace jsoner_space;

#define ARRAY_NODE "array"
#define OBJECT_NODE "object"
#define STRING_NODE "string"
#define NONE_NODE ""

JsonParser::JsonParser()
{
    root = new JsonContainer(OBJECT);
}

JsonParser::JsonParser(const JsonParser &other)
{
    root = new JsonContainer(OBJECT);
    JsonContainer *child = new JsonContainer;
    addChild(&root, &child);
    copyElements(&root, other.root);
    deleteNoneElements(&root);
}

JsonParser::JsonParser(JsonParser &&other)
{
    this->root = other.root;
    other.root = nullptr;
}

JsonParser::JsonParser(JsonContainer *other)
{
    root = new JsonContainer(OBJECT);
    JsonContainer *child = new JsonContainer;
    addChild(&root, &child);
    copyElements(&(root->down), other);
    deleteNoneElements(&root);
}

JsonParser::~JsonParser()
{
    eraseJsonContainer(&root);
}

JsonParser& JsonParser::operator=(const JsonParser &other)
{
    if(this != &other)
    {
        this->eraseJsonContainer(&root);
        root = new JsonContainer(OBJECT);
        JsonContainer *child = new JsonContainer;
        addChild(&root, &child);
        copyElements(&(root->down), other.root);
        deleteNoneElements(&root);
    }
    return *this;
}

typeCell JsonParser::getType(std::string sourceStr) const
{
    if(sourceStr == "{")
        return OBJECT;
    if(sourceStr == "}")
        return END_OBJECT;
    if(sourceStr == "[")
        return ARRAY;
    if(sourceStr == "]")
        return END_ARRAY;

    return STRING;
}

void JsonParser::eraseJsonContainer(JsonContainer **root)
{
    JsonContainer *temp = *root;

    if(temp->down != nullptr)
        eraseJsonContainer(&temp->down);
    if(temp->next != nullptr)
        eraseJsonContainer(&temp->next);

    if((temp->next == nullptr) && (temp->down == nullptr) && (temp != nullptr))
    {
        delete temp;
        return;
    }
}

void JsonParser::addChild(JsonContainer **node, JsonContainer **newContainer)
{
    JsonContainer *temp = *node;
    temp->down = *newContainer;
    (*newContainer)->up = temp;
}

void JsonParser::addNeighbord(JsonContainer **node, JsonContainer **newContainer)
{
    JsonContainer *temp = *node;
    temp->next = *newContainer;
    (*newContainer)->prev = temp;
    (*newContainer)->up = temp->up;
}

void JsonParser::getFromStream(std::istream &in, JsonContainer **node)
{
    JsonContainer *tempNode = *node;
    std::string inputStr;
    std::string firstPartStr;
    std::string secondPartStr;
    while(std::getline(in, inputStr))
    {
        std::list<std::string> parsed = parser_string_space::parse_by_delimeter(inputStr, ":", true);
        if(parsed.size() > 1)
        {
            std::list<std::string>::iterator it = std::next(parsed.begin(), 0);
            firstPartStr = *it;
            it = std::next(parsed.begin(), 1);
            secondPartStr = *it;

            firstPartStr = parser_string_space::delete_symbol(firstPartStr, parser_string_space::TAB);
            firstPartStr = parser_string_space::delete_symbol(firstPartStr, parser_string_space::COMMA);
            firstPartStr = parser_string_space::delete_symbol(firstPartStr, parser_string_space::DQUOTE);
            firstPartStr = parser_string_space::delete_symbol(firstPartStr, parser_string_space::SPACE);
        }
        else
        {
            firstPartStr = "";
            std::list<std::string>::iterator it = std::next(parsed.begin(), 0);
            secondPartStr = *it;
        }

        secondPartStr = parser_string_space::delete_symbol(secondPartStr, parser_string_space::TAB);
        secondPartStr = parser_string_space::delete_symbol(secondPartStr, parser_string_space::COMMA);
        secondPartStr = parser_string_space::delete_symbol(secondPartStr, parser_string_space::DQUOTE);
        secondPartStr = parser_string_space::delete_symbol(secondPartStr, parser_string_space::SPACE);

        typeCell type = getType(parser_string_space::delete_symbol(secondPartStr, parser_string_space::SPACE));
        if((type == END_ARRAY) || (type == END_OBJECT))
        {
            /*temp_node->prev->next = nullptr;
            delete temp_node;*/
            return;
        }

        tempNode->setData(firstPartStr, secondPartStr, type);

        if((type == OBJECT) || (type == ARRAY))
        {
            JsonContainer *temp = new JsonContainer;
            addChild(&tempNode, &temp);
            getFromStream(in, &(tempNode->down));
        }
        JsonContainer *temp = new JsonContainer;
        addNeighbord(&tempNode, &temp);
        tempNode = tempNode->next;
        /*if(type == STRING)
        {
            json_container *temp = new json_container;
            add_neighbord(&temp_node, &temp);
            temp_node = temp_node->next;
        }*/
    }
}

void JsonParser::putToStream(std::ostream &out, JsonContainer **node, int32_t offset)
{
    JsonContainer *temp = *node;
    std::string outStr;
    while(true)
    {
        if((temp->cellType == OBJECT) || (temp->cellType == ARRAY))
        {
            outStr = std::string("\t", offset) + temp->oneCell.first + " : " + temp->oneCell.second + "\n";
            if(temp->oneCell.first != "")
                out.write(outStr.c_str(), outStr.size());
            else out.write(std::string(temp->oneCell.second + "\n").c_str(), temp->oneCell.second.size() + 1);
            putToStream(out, &(temp->down), offset + 1);
        }
        if(temp->cellType == STRING)
        {
            outStr = std::string("\t", offset) + temp->oneCell.first + " : " + temp->oneCell.second + ",\n";
            out.write(outStr.c_str(), outStr.size());
        }
        if(temp->next == nullptr)
            break;
        temp = temp->next;
    }
    if((temp->up->cellType == OBJECT) || (temp->up->cellType == ARRAY))
    {
        if(temp->up->next != nullptr)
        {
            outStr.clear();
            outStr.push_back(static_cast<char>(temp->up->cellType));
            outStr.push_back('\n');
            out.write(outStr.c_str(), outStr.size());
        }
        else
        {
            outStr.clear();
            outStr.push_back(static_cast<char>(temp->up->cellType));
            outStr.push_back('\n');
            out.write(outStr.c_str(), outStr.size());
        }
    }
}

void JsonParser::copyElements(JsonContainer **node, const JsonContainer *other)
{
    if(other == nullptr)
        return;
    JsonContainer *tempNode = *node;
    const JsonContainer *tempOther = other;

    if(tempOther->cellType == NONE)
        copyElements(&tempNode, tempOther->down);

    for(; tempOther != nullptr; tempOther = tempOther->next)
    {
        tempNode->setData(tempOther->oneCell.first, tempOther->oneCell.second, tempOther->cellType);

        if((tempOther->cellType == OBJECT) || (tempOther->cellType == ARRAY))
        {
            JsonContainer *temp = new JsonContainer;
            addChild(&tempNode, &temp);
            copyElements(&(tempNode->down), tempOther->down);
        }
        JsonContainer *temp = new JsonContainer;
        addNeighbord(&tempNode, &temp);
        tempNode = tempNode->next;
    }
}

void JsonParser::deleteNoneElements(JsonContainer **node)
{
    JsonContainer *temp = *node;

    for(;;)
    {
        if(temp->down != nullptr)
            deleteNoneElements(&(temp->down));
        if(temp->next == nullptr)
            break;
        temp = temp->next;
    }
    while((temp->cellType == NONE) && (temp->prev != nullptr))
    {
        JsonContainer *prev = temp->prev;
        delete temp;
        temp = prev;
        temp->next = nullptr;
    }
}

void JsonParser::getJson(std::istream &inputStream)
{
    eraseJsonContainer(&root);
    root = new JsonContainer(OBJECT);
    getFromStream(inputStream, &root);
    deleteNoneElements(&root);
}

void JsonParser::setJson(std::ostream &outputStream)
{
    putToStream(outputStream, &root, 0);
}

JsonContainer* JsonParser::findElementByName(std::string name)
{
    return this->findElementByName(root, name);
}

JsonContainer* JsonParser::findElementByName(JsonContainer *node, std::string name)
{
    JsonContainer *temp = node;
    for(; temp != nullptr; temp = temp->next)
    {
        if(temp->oneCell.first == name)
            return temp;
        if(temp->cellType != STRING)
        {
            JsonContainer *returnType = findElementByName(temp->down, name);
            if(returnType != nullptr)
                return returnType;
        }
    }
    return nullptr;
}

void JsonParser::findElementsByName(JsonContainer *node, std::list<JsonContainer*> &foundedList, std::string name)
{
    JsonContainer *tempPtr = node;
    for(; tempPtr != nullptr; tempPtr = tempPtr->next)
    {
        if(tempPtr->oneCell.first == name)
            foundedList.push_back(tempPtr);

        if(tempPtr->cellType == OBJECT)
            this->findElementsByName(tempPtr->down, foundedList, name);
    }
}

std::list<JsonContainer*> JsonParser::findElementsByName(std::string name)
{
    std::list<JsonContainer*> foundedElements;
    this->findElementsByName(root, foundedElements, name);
    return foundedElements;
}

JsonContainer* JsonParser::findElementByTemplate(std::string templateString)
{

}

std::list<JsonContainer*> JsonParser::findElementsByTemplate(std::string templateString)
{

}

//--------------------------------------GET JSON DATA---------------------------------------------

JsonParser getJsonData(std::string filename)
{
    std::ifstream fin;
    fin.open(filename.c_str());
    if(fin.is_open() == false)
        throw SIEM_errors::SIEMException("Cannot open file: " + filename);

    JsonParser return_parser;
    return_parser.getJson(fin);
    return return_parser;
}


//------------------------------------TYPE JSON NODE RESOLVER--------------------------------------

JSONNodeTypeResolver::JSONNodeTypeResolver()
{

}

JSONNodeTypeResolver& JSONNodeTypeResolver::getInstance()
{
    static JSONNodeTypeResolver instance;
    return instance;
}

typeCell JSONNodeTypeResolver::getNodeType(const std::string &nodeName)
{
    if(nodeName == "object")
        return OBJECT;
    else if(nodeName == "array")
        return ARRAY;
    else if(nodeName == "string")
        return STRING;
    else
        return NONE;
}

std::string JSONNodeTypeResolver::getNodeName(const typeCell &typeNode)
{
    if(typeNode == OBJECT)
        return OBJECT_NODE;
    else if(typeNode == ARRAY)
        return ARRAY_NODE;
    else if(typeNode == STRING)
        return STRING_NODE;
    else
        return NONE_NODE;
}
