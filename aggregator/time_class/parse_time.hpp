#ifndef PARSE_TIME_HPP
#define PARSE_TIME_HPP

#include "../parser_txt/parser.hpp"

namespace data_time_space
{
    enum monthType{ JANUARY_NUM = 1, FEBRUARY_NUM = 2, MARCH_NUM = 3, APRIL_NUM = 4, MAY_NUM = 5,
         JUNE_NUM = 6, JULY_NUM = 7, AUGUST_NUM = 8, SEPTEMBER_NUM = 9, OCTOBER_NUM = 10,
         NOVEMBER_NUM = 11, DECEMBER_NUM = 12, INCORRECT_NUM = 13};

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

    monthType getMonthType(std::string monthString);
    std::string getMonthString(monthType monthTypeRepresentation);
}

#endif
