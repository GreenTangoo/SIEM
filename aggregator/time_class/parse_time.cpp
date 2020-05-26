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

std::string data_time_space::getMonthString(data_time_space::monthType monthTypeRepr)
{
    std::string convertedMonth;

    switch(monthTypeRepr)
    {
    case JANUARY_NUM:
        convertedMonth = "January";
        break;
    case FEBRUARY_NUM:
        convertedMonth = "February";
        break;
    case MARCH_NUM:
        convertedMonth = "March";
        break;
    case APRIL_NUM:
        convertedMonth = "April";
        break;
    case MAY_NUM:
        convertedMonth = "May";
        break;
    case JUNE_NUM:
        convertedMonth = "June";
        break;
    case JULY_NUM:
        convertedMonth = "July";
        break;
    case AUGUST_NUM:
        convertedMonth = "August";
        break;
    case SEPTEMBER_NUM:
        convertedMonth = "September";
        break;
    case OCTOBER_NUM:
        convertedMonth = "October";
        break;
    case NOVEMBER_NUM:
        convertedMonth = "November";
        break;
    case DECEMBER_NUM:
        convertedMonth = "December";
        break;
    default:
        convertedMonth = "Incorrect num";
    }

    return convertedMonth;
}

data_time_space::monthType data_time_space::getMonthType(std::string monthString)
{
    if(monthString == "January")
        return JANUARY_NUM;
    else if(monthString == "February")
        return FEBRUARY_NUM;
    else if(monthString == "March")
        return MARCH_NUM;
    else if(monthString == "April")
        return APRIL_NUM;
    else if(monthString == "May")
        return MAY_NUM;
    else if(monthString == "June")
        return JUNE_NUM;
    else if(monthString == "July")
        return JULY_NUM;
    else if(monthString == "August")
        return AUGUST_NUM;
    else if(monthString == "September")
        return SEPTEMBER_NUM;
    else if(monthString == "October")
        return OCTOBER_NUM;
    else if(monthString == "November")
        return NOVEMBER_NUM;
    else if(monthString == "December")
        return DECEMBER_NUM;
    else return INCORRECT_NUM;
}
