

#include "apache_aggr.hpp"

using namespace aggregator_space;

ApacheAggregator::ApacheAggregator(const std::string &logFilename, const std::string &resultJsonFilename) : resultJsonFilename(resultJsonFilename)
{
    logFileFilename = logFilename;
}

ApacheAggregator::ApacheAggregator(const ApacheAggregator &other)
{
    logFileFilename = other.logFileFilename;
    jsonLogRepresentation = other.jsonLogRepresentation;
}

ApacheAggregator::~ApacheAggregator()
{

}

void ApacheAggregator::getInformationFromLogs()
{
    jsonLogRepresentation = getJsonData(resultJsonFilename);

    std::ifstream fin;
    fin.open(logFileFilename);
    if(fin.is_open() == false)
    {
        throw SIEM_errors::SIEMException("Cannot open file: " + logFileFilename);
    }

    std::string oneLineFromLogfile;
    while(std::getline(fin, oneLineFromLogfile))
    {
        std::list<std::string> parsedStringList = parser_string_space::parse_by_delimeter(oneLineFromLogfile, " ");
        std::list<std::string>::iterator ipIter = std::next(parsedStringList.begin(), 0);
        jsonLogRepresentation.addEmptyNode(*ipIter, "requests");

        std::list<std::string>::iterator timeIter = std::next(parsedStringList.begin(), 3);
        std::string timeString = this->convertApacheDateFormat(*timeIter);
        jsonLogRepresentation.addString(std::pair<std::string, std::string>("time", timeString), *ipIter);

        std::list<std::string>::iterator pathIter = std::next(parsedStringList.begin(), 6);
        jsonLogRepresentation.addString(std::pair<std::string, std::string>("path", *pathIter), *ipIter);

        std::list<std::string>::iterator responseCodeIter = std::next(parsedStringList.begin(), 8);
        jsonLogRepresentation.addString(std::pair<std::string, std::string>("response code", *responseCodeIter), *ipIter);
    }

    fin.close();

    std::ofstream fout(resultJsonFilename, std::ios_base::trunc);
    jsonLogRepresentation.setJson(fout, false);
    fout.close();
}

/*---------------------------------APACHE AGGREGATOR(PRIVATE)------------------------------------------*/

std::string ApacheAggregator::convertApacheDateFormat(std::string apacheDate)
{
    //std::copy(apacheDate.begin() + 1, apacheDate.end(), dateString.begin()); // delete [ symbol from apacheDate
    std::string::size_type pos = apacheDate.find("[");
    std::string dateString(apacheDate.substr(pos + 1));

    std::list<std::string> parsedDateStringList = parser_string_space::parse_by_delimeter(dateString, "/");
    std::list<std::string>::iterator monthIter = std::next(parsedDateStringList.begin(), 1);

    int monthNumber = data_time_space::getMonthType(*monthIter);

    std::list<std::string>::iterator dayIter = std::next(parsedDateStringList.begin(), 0);
    std::list<std::string>::iterator timeIter = std::next(parsedDateStringList.begin(), 2);

    std::string convertedDateTime = *dayIter + "/" + std::to_string(monthNumber) + "/" + *timeIter;
    return convertedDateTime;
}
