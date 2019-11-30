#ifndef LOGIN_ROOT_SYMPTOMS_HPP
#define LOGIN_ROOT_SYMPTOMS_HPP

#include <string>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace account_access
    {
        class LoginRootSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            LoginRootSymptoms(std::string filename);
            LoginRootSymptoms(const LoginRootSymptoms &other) = default;
            LoginRootSymptoms(LoginRootSymptoms &&other) = default;
            ~LoginRootSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
