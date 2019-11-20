#ifndef USER_LOGIN_SYMPTOMS_HPP
#define USER_LOGIN_SYMPTOMS_HPP

#include <fstream>
#include <string>

#include "../../symptoms_interface/main_symp_interface.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace account_access
    {
        class UserLoginSymptoms : public Symptom
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
            std::string warning_msg();
            std::vector<data> getData();
        };
    }
}

#endif
