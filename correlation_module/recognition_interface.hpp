#ifndef RECOGNITION_INTERFACE
#define RECOGNITION_INTERFACE

#include <vector>

template<class T>
class problem_recognition
{
private:
    problem_recognition& operator=(const problem_recognition &other) = delete;
public:
    problem_recognition() = default;
    problem_recognition(const problem_recognition &other) = default;
    problem_recognition(problem_recognition &&other) = default;
    virtual ~problem_recognition() = default;
    virtual std::vector<std::pair<double, T>> checkSymptoms() = 0;
};

#endif
