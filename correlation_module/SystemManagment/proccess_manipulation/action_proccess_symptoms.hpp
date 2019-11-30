#ifndef ACTION_PROCCESS_SYMPTOMS_HPP
#define ACTION_PROCCESS_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace proccess_manipulation
    {
        class ActionProccessSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            ActionProccessSymptoms(std::string filename);
            ActionProccessSymptoms(const ActionProccessSymptoms &other) = default;
            ActionProccessSymptoms(ActionProccessSymptoms &&other) = default;
            ~ActionProccessSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
