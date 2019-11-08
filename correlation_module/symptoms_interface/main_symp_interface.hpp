#ifndef MAIN_SYMP_INTERFACE_HPP
#define MAIN_SYMP_INTERFACE_HPP

#include <string>
#include <vector>

namespace symptoms
{
    class Symptom
    {
    protected:
        std::vector<Symptom*> binds;
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
