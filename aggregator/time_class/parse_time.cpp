#include "parse_time.hpp"

data_time::time::time(): year(0), month(0), day(0), absolute_one_day_time(0)
{

}

data_time::time::time(std::string str_time): year(0), month(0), day(0), absolute_one_day_time(0)
{
    setTime(str_time);
}

data_time::time::~time()
{

}

data_time::time::time(const time &other)
{
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->absolute_one_day_time = other.absolute_one_day_time;
}

data_time::time& data_time::time::operator=(const time &other)
{
    if(this != &other)
    {
        this->year = other.year;
        this->month = other.month;
        this->day = other.day;
        this->absolute_one_day_time = other.absolute_one_day_time;
    }
    return *this;
}

void data_time::time::setTime(std::string str_time)
{
    std::list<std::string> parsed_str = parser_string::parse_by_delimeter(str_time, "/"); // Get year, month, day, day time
    std::list<std::string>::iterator access_iter = std::next(parsed_str.begin(), 0); // Get year
    this->year = atoi(access_iter->c_str());

    access_iter = std::next(parsed_str.begin(), 1); // Get month
    this->month = atoi(access_iter->c_str());

    access_iter = std::next(parsed_str.begin(), 2); // Get day
    this->day = atoi(access_iter->c_str());

    access_iter = std::next(parsed_str.begin(), 3); // Get day time
    transformToAbsoluteTime(*access_iter);
}

std::string data_time::time::getStrTime()
{
    int hour = absolute_one_day_time / 3600;
    absolute_one_day_time %= 3600;
    int minute = absolute_one_day_time / 60;
    absolute_one_day_time %= 60;
    int second = absolute_one_day_time;

    std::string return_str_time = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day) + "/"
                    + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
    return return_str_time;
}

int data_time::time::getYear() const
{
    return year;
}

int data_time::time::getMonth() const
{
    return month;
}

int data_time::time::getDay() const
{
    return day;
}

int data_time::time::getAbsoluteTime() const
{
    return absolute_one_day_time;
}

void data_time::time::transformToAbsoluteTime(std::string str_time)
{
    std::list<std::string> parsed_str = parser_string::parse_by_delimeter(str_time, ":"); // Get hour, minute, second

    std::list<std::string>::iterator access_iter = std::next(parsed_str.begin(), 0); // Get hour
    int hour = atoi(access_iter->c_str());

    access_iter = std::next(parsed_str.begin(), 1); // Get minute
    int minute = atoi(access_iter->c_str());

    access_iter = std::next(parsed_str.begin(), 2); // Get second
    int second = atoi(access_iter->c_str());

    absolute_one_day_time = second + minute * 60 + hour * 3600;
}

int data_time::compare(const data_time::time &first, const data_time::time &second)
{
    if(first.getYear() != second.getYear())
        return first.getYear() > second.getYear() ? 1 : 0;
    if(first.getMonth() != second.getMonth())
        return first.getMonth() > second.getMonth() ? 1 : 0;
    if(first.getDay() != second.getDay())
        return first.getDay() > second.getDay() ? 1 : 0;
    if(first.getAbsoluteTime() != second.getAbsoluteTime())
        return first.getAbsoluteTime() > second.getAbsoluteTime() ? 1 : 0;

    return -1;
}
