#ifndef REPEATER_SYMPTOMS
#define REPEATER_SYMPTOMS

#include <iostream>

namespace dos_symptoms
{
    struct params
    {
        int32_t requests_threshold;
        int32_t time_interval;
    };
    bool amount_requests();
    bool check_dos();
    void set_params(int32_t requests_thresh, int32_t interval);
}

namespace port_scan_symptoms
{

}

namespace bruteforce_symptoms
{

}
#endif
