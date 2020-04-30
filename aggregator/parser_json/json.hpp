#ifndef JSON_H
#define JSON_H

#include <fstream>

#include "../parser_txt/parser.hpp"
#include "../../error_handler_module/handler.hpp"

namespace jsoner_space
{
    enum typeCell {OBJECT = '}', ARRAY = ']', STRING, END_OBJECT = '{', END_ARRAY = '[', NONE};
    struct JsonContainer
    {
        std::pair<std::string, std::string> oneCell;
        typeCell cellType;

        JsonContainer *next;
        JsonContainer *prev;
        JsonContainer *down;
        JsonContainer *up;

        explicit JsonContainer()
        {
            next = prev = down = up = nullptr;
            cellType = NONE;
        }
        explicit JsonContainer(typeCell cellType)
        {
            next = prev = down = up = nullptr;
            this->cellType = cellType;
        }
        explicit JsonContainer(std::string firstStr, std::string secondStr, typeCell cellType)
        {
            next = prev = down = up = nullptr;
            oneCell.first = firstStr;
            oneCell.second = secondStr;
            this->cellType = cellType;
        }
        void setData(std::string firstStr, std::string secondStr, typeCell cellType)
        {
            oneCell.first = firstStr;
            oneCell.second = secondStr;
            this->cellType = cellType;
        }
    };


    class JsonParser
    {
    private:
        JsonContainer *root;
    private:
        void eraseJsonContainer(JsonContainer **root);
        void addChild(JsonContainer **node, JsonContainer **newContainer);
        void addNeighbord(JsonContainer **node, JsonContainer **newContainer);
        JsonContainer* findElementByName(JsonContainer *node, std::string name);
        typeCell getType(std::string sourceStr) const;
        void getFromStream(std::istream &in, JsonContainer **node);
        void putToStream(std::ostream &out, JsonContainer **node, int32_t offset);
        void copyElements(JsonContainer **node, const JsonContainer *other);
        void deleteNoneElements(JsonContainer **node);
    public:
        JsonParser();
        JsonParser(const JsonParser &other);
        JsonParser(JsonParser &&other);
        JsonParser(JsonContainer *other);
        ~JsonParser();
        JsonParser& operator=(const JsonParser &other);
        void getJson(std::istream &input_stream);
        void setJson(std::ostream &output_stream);
        JsonContainer* findElementByName(std::string name);
        std::list<JsonContainer*> findElementsByName(std::string name);
    };
}

jsoner_space::JsonParser getJsonData(std::string filename);

#endif
