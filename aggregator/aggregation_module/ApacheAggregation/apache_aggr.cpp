#include "apache_aggr.hpp"

using namespace aggregator_space;
using namespace parser_string_space;

#define REQUESTS "requests"
#define ROOT "root"
#define TIME "time"
#define PATH "path"
#define RESPONSE_CODE "response-code"

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

    std::string requestsPath = constructPath(SLASH, 2, ROOT, REQUESTS);
    jsonLogRepresentation.addOrUpdateNode(REQUESTS, requestsPath.c_str());

    std::map<std::string, std::map<std::string, int>> counterResponsesCode;

    std::string oneLineFromLogfile;
    while(std::getline(fin, oneLineFromLogfile))
    {
        std::list<std::string> parsedStringList = parser_string_space::parse_by_delimeter(oneLineFromLogfile, " ");
        std::list<std::string>::iterator ipIter = std::next(parsedStringList.begin(), 0);
        std::string addIpPath = constructPath(SLASH, 3, ROOT, REQUESTS, (*ipIter).c_str());
        jsonLogRepresentation.addOrUpdateNode(*ipIter, addIpPath);

        std::list<std::string>::iterator timeIter = std::next(parsedStringList.begin(), 3);
        std::string timeString = convertApacheDateFormat(*timeIter);
        std::string addTimePath = constructPath(SLASH, 4, ROOT, REQUESTS, (*ipIter).c_str(), TIME);
        jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(TIME, timeString), addTimePath);

        std::string addPathPath = constructPath(SLASH, 4, ROOT, REQUESTS, (*ipIter).c_str(), PATH);
        jsonLogRepresentation.addOrUpdateArray(PATH, std::vector<std::string>(), addPathPath);
        std::list<std::string>::iterator pathIter = std::next(parsedStringList.begin(), 6);
        jsonLogRepresentation.addArrayElement(*pathIter, addPathPath);

        std::list<std::string>::iterator responseCodeIter = std::next(parsedStringList.begin(), 8);

        counterResponsesCode[*ipIter][*responseCodeIter]++;
        int amountResponseCode = counterResponsesCode[*ipIter][*responseCodeIter];
        std::string responseCodeNumber = "response-code-" + *responseCodeIter;

        std::string responseCodeNumberPath = constructPath(SLASH, 4, ROOT, REQUESTS, (*ipIter).c_str(), responseCodeNumber.c_str());
        jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(responseCodeNumber, std::to_string(amountResponseCode)),
                                                responseCodeNumberPath);
    }

    fin.close();

    std::ofstream fout(resultJsonFilename, std::ios_base::trunc);
    jsonLogRepresentation.setJson(fout, false);
    fout.close();
}

/*---------------------------------APACHE AGGREGATOR(PRIVATE)------------------------------------------*/

std::string ApacheAggregator::convertApacheDateFormat(std::string apacheDate)
{
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
