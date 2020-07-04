#include "system_auth_aggr.hpp"

using namespace aggregator_space;
using namespace parser_string_space;
using namespace data_time_space;

#define ROOT "root"
#define USERS "users"
#define ADMIN "admin"
#define TIME "time"
#define IP "ip"

SystemAuthAggregator::SystemAuthAggregator(const std::string &logFilename, const std::string &resultJsonFilename) : resultJsonFilename(resultJsonFilename)
{
    logFileFilename = logFilename;
}

SystemAuthAggregator::SystemAuthAggregator(const SystemAuthAggregator &other)
{
    logFileFilename = other.logFileFilename;
    jsonLogRepresentation = other.jsonLogRepresentation;
}

SystemAuthAggregator::~SystemAuthAggregator()
{

}

void SystemAuthAggregator::getInformationFromLogs()
{
    jsonLogRepresentation = getJsonData(resultJsonFilename);

    std::ifstream fin;
    fin.open(logFileFilename);
    if(fin.is_open() == false)
    {
        throw SIEM_errors::SIEMException("Cannot open file: " + logFileFilename);
    }

    std::string usersPath = constructPath(SLASH, 2, ROOT, USERS);
    jsonLogRepresentation.addOrUpdateNode(USERS, usersPath);

    std::string adminPath = constructPath(SLASH, 2, ROOT, ADMIN);
    jsonLogRepresentation.addOrUpdateNode(ADMIN, adminPath);

    std::string oneLineFromLogfile;
    while(std::getline(fin, oneLineFromLogfile))
    {
        std::list<std::string> parsedStringList = parser_string_space::parse_by_delimeter(oneLineFromLogfile, " ");
        std::list<std::string>::iterator accessResultIter = std::next(parsedStringList.begin(), 5);

        if(*accessResultIter == "Accepted")
        {
            std::list<std::string>::iterator nameIter = std::next(parsedStringList.begin(), 8);
            std::string namePath = constructPath(SLASH, 3, ROOT, USERS, nameIter->c_str());
            jsonLogRepresentation.addOrUpdateNode(*nameIter, namePath);

            std::list<std::string>::iterator ipIter = std::next(parsedStringList.begin(), 10);
            std::string ipPath = constructPath(SLASH, 4, ROOT, USERS, nameIter->c_str(), IP);
            jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(IP, *ipIter), ipPath);

            std::string timeStr = constructTimeString(parsedStringList);
            std::string timePath = constructPath(SLASH, 4, ROOT, USERS, nameIter->c_str(), TIME);
            jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(TIME, timeStr), timePath);
        }
    }

    fin.close();

    std::ofstream fout(resultJsonFilename, std::ios_base::trunc);
    jsonLogRepresentation.setJson(fout, false);
    fout.close();
}

std::string SystemAuthAggregator::constructTimeString(std::list<std::string> parsedStringList)
{
    std::list<std::string>::iterator monthIter = std::next(parsedStringList.begin(), 0);
    monthType month = getMonthType(*monthIter);

    std::list<std::string>::iterator dayIter = std::next(parsedStringList.begin(), 1);
    std::list<std::string>::iterator timeIter = std::next(parsedStringList.begin(), 2);

    std::string timeStr = std::to_string(static_cast<int>(month)) + "/" + *dayIter + "/" + *timeIter;

    return timeStr;
}
