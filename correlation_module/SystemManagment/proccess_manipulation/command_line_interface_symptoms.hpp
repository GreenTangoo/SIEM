#ifndef COMMAND_LINE_INTERFACE_SYMPTOMS_HPP
#define COMMAND_LINE_INTERFACE_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class CommandLineInterfaceSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            CommandLineInterfaceSymptoms(std::string filename);
            CommandLineInterfaceSymptoms(const CommandLineInterfaceSymptoms &other) = default;
            CommandLineInterfaceSymptoms(CommandLineInterfaceSymptoms &&other) = default;
            ~CommandLineInterfaceSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
