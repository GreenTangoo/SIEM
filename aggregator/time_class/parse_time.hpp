#ifndef PARSE_TIME_HPP
#define PARSE_TIME_HPP

#include "../parser_txt/parser.hpp"

namespace data_time_space
{
    class Time
    {
    private:
        int year;
        int month;
        int day;
        int absoluteOneDayTime;
    private:
        void transformToAbsoluteTime(std::string strTime);
    public:
        explicit Time(std::string strTime); // Format: year/month/day/hour:minute:second
        explicit Time();
        Time(const Time &other);
        Time(Time &&other) = delete;
        ~Time();
        Time& operator=(const Time &other);
        bool operator==(const Time &other);
        friend int compare(const Time &first, const Time &second);
        void setTime(std::string strTime); // Format: year/month/day/hour:minute:second
        std::string getStrTime();
        int getAbsoluteTime() const;
        static int getAbsoluteTime(std::string timeStr);
        int getYear() const ;
        int getMonth() const ;
        int getDay() const ;
    };
}

#endif
