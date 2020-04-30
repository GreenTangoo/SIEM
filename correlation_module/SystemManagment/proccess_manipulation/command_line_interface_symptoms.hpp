#ifndef COMMAND_LINE_INTERFACE_SYMPTOMS_HPP
#define COMMAND_LINE_INTERFACE_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace proccess_manipulation
    {
        class CommandLineInterfaceSymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
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
