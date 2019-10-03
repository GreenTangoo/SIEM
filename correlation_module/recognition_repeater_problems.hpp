#ifndef RECOGNITION_REPEATER_PROBLEM
#define RECOGNITION_REPEATER_PROBLEM

#include "recognition_interface.hpp"
#include "sypmtoms_namespace/repeater_symptoms.hpp"

namespace repeater
{
    enum type_repeater_problems
    {
        DOS, DDOS, PORT_SCAN, BRUTEFORCE
    };

    template<class T>
    class repeater_problems : public problem_recognition<T>
    {
    private:
        type_repeater_problems type_problem_detected;
        double probability;
    public:
        repeater_problems();
        repeater_problems(const repeater_problems &other);
        repeater_problems(repeater_problems &&other);
        virtual ~repeater_problems();
        virtual std::vector<std::pair<double, T>> checkSymptoms();
    };
}

#endif
