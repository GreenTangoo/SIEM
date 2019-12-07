#ifndef PARSE_TIME_HPP
#define PARSE_TIME_HPP

#include "../parser_txt/parser.hpp"

namespace data_time
{
    class time
    {
    private:
        int year;
        int month;
        int day;
        int absolute_one_day_time;
    private:
        void transformToAbsoluteTime(std::string str_time);
    public:
        explicit time(std::string str_time); // Format: year/month/day/hour:minute:second
        explicit time();
        time(const time &other);
        time(time &&other) = delete;
        ~time();
        time& operator=(const time &other);
        bool operator==(const time &other);
        friend int compare(const time &first, const time &second);
        void setTime(std::string str_time); // Format: year/month/day/hour:minute:second
        std::string getStrTime();
        int getAbsoluteTime() const;
        int getYear() const ;
        int getMonth() const ;
        int getDay() const ;
    };
}

#endif
