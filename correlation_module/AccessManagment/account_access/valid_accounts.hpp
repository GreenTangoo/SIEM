#ifndef VALID_ACCOUNTS_HPP
#define VALID_ACCOUNTS_HPP

#include "../../symptoms_interface/symp_implementation.hpp"

namespace symptoms_space
{
    namespace account_access
    {
        class ValidAccountsSymptoms : public SymptomImpl
        {
        private:
            json_space::JsonObject parser;
            std::string jsonFilename;
        public:
            ValidAccountsSymptoms(std::string filename);
            ValidAccountsSymptoms(const ValidAccountsSymptoms &other) = default;
            ValidAccountsSymptoms(ValidAccountsSymptoms &&other) = default;
            ~ValidAccountsSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif // VALID_ACCOUNTS_HPP
