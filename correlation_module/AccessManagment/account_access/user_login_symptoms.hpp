#ifndef USER_LOGIN_SYMPTOMS_HPP
#define USER_LOGIN_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms
{
    namespace account_access
    {
        class UserLoginSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            UserLoginSymptoms(std::string filename);
            UserLoginSymptoms(const UserLoginSymptoms &other) = default;
            UserLoginSymptoms(UserLoginSymptoms &&other) = default;
            ~UserLoginSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
