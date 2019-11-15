#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <string>
#include <vector>

namespace symptoms
{
    class Symptom
    {
    protected:
        struct data
        {
            std::vector<std::string> main_data;
        };
        std::vector<data> data_from_all_symptoms;
    public:
        Symptom() = default;
        Symptom(const Symptom &other) = delete;
        Symptom(Symptom &&other) = default;
        virtual ~Symptom() = default;
        virtual bool checkSymptoms() = 0;
        virtual std::string warning_msg() = 0;
        virtual data getData() = 0;
    };
}

#endif
