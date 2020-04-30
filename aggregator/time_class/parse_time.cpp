#include "parse_time.hpp"

data_time_space::Time::Time(): year(0), month(0), day(0), absoluteOneDayTime(0)
{

}

data_time_space::Time::Time(std::string strTime): year(0), month(0), day(0), absoluteOneDayTime(0)
{
    setTime(strTime);
}

data_time_space::Time::~Time()
{

}

data_time_space::Time::Time(const Time &other)
{
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->absoluteOneDayTime = other.absoluteOneDayTime;
}

data_time_space::Time& data_time_space::Time::operator=(const Time &other)
{
    if(this != &other)
    {
        this->year = other.year;
        this->month = other.month;
        this->day = other.day;
        this->absoluteOneDayTime = other.absoluteOneDayTime;
    }
    return *this;
}

bool data_time_space::Time::operator==(const Time &other)
{
    if(this == &other)
        return true;
    return ((this->year == other.year) && (this->month == other.month) && (this->day == other.day) && (this->absoluteOneDayTime == other.absoluteOneDayTime));
}

void data_time_space::Time::setTime(std::string strTime)
{
    std::list<std::string> parsedStr = parser_string_space::parse_by_delimeter(strTime, "/"); // Get year, month, day, day time
    std::list<std::string>::iterator accessIter = std::next(parsedStr.begin(), 0); // Get year
    this->year = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 1); // Get month
    this->month = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 2); // Get day
    this->day = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 3); // Get day time
    transformToAbsoluteTime(*accessIter);
}

std::string data_time_space::Time::getStrTime()
{
    int hour = absoluteOneDayTime / 3600;
    absoluteOneDayTime %= 3600;
    int minute = absoluteOneDayTime / 60;
    absoluteOneDayTime %= 60;
    int second = absoluteOneDayTime;

    std::string returnStrTime = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day) + "/"
                    + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);

    return returnStrTime;
}

int data_time_space::Time::getYear() const
{
    return year;
}

int data_time_space::Time::getMonth() const
{
    return month;
}

int data_time_space::Time::getDay() const
{
    return day;
}

int data_time_space::Time::getAbsoluteTime() const
{
    return absoluteOneDayTime;
}

int data_time_space::Time::getAbsoluteTime(std::string timeStr)
{
    std::list<std::string> parsedStr = parser_string_space::parse_by_delimeter(timeStr, ":"); // Get hour, minute, second

    std::list<std::string>::iterator accessIter = std::next(parsedStr.begin(), 0); // Get hour
    int hour = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 1); // Get minute
    int minute = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 2); // Get second
    int second = atoi(accessIter->c_str());

    int innerAbsoluteOneDayTime = second + minute * 60 + hour * 3600;
    return innerAbsoluteOneDayTime;
}

void data_time_space::Time::transformToAbsoluteTime(std::string strTime)
{
    std::list<std::string> parsedStr = parser_string_space::parse_by_delimeter(strTime, ":"); // Get hour, minute, second

    std::list<std::string>::iterator accessIter = std::next(parsedStr.begin(), 0); // Get hour
    int hour = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 1); // Get minute
    int minute = atoi(accessIter->c_str());

    accessIter = std::next(parsedStr.begin(), 2); // Get second
    int second = atoi(accessIter->c_str());

    absoluteOneDayTime = second + minute * 60 + hour * 3600;
}

int data_time_space::compare(const data_time_space::Time &first, const data_time_space::Time &second)
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
