#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <string>

namespace symptoms
{
    class Symptom
    {
    public:
        Symptom() = default;
        Symptom(const Symptom &other) = delete;
        Symptom(Symptom &&other) = default;
        virtual ~Symptom() = default;
        virtual bool checkSymptoms() = 0;
        virtual std::string warning_msg() = 0;
    };
}

#endif
