#ifndef USER_LOGIN_SYMPTOMS_HPP
#define USER_LOGIN_SYMPTOMS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace account_access
    {
        class UserLoginSymptoms : public SymptomImpl
        {
        private:
            jsoner_space::JsonParser parser;
            std::string jsonFilename;
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
