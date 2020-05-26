#ifndef LOGIN_ROOT_SYMPTOMS_HPP
#define LOGIN_ROOT_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace account_access
    {
        class LoginRootSymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
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
