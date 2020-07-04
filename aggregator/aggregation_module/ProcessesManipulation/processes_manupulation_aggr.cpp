#include "processes_manupulation_aggr.hpp"

using namespace aggregator_space;
using namespace parser_string_space;

#define ROOT "root"
#define USERS "users"

ProcManipulationAggregator::ProcManipulationAggregator(const std::string &logFilename, const std::string &resultJsonFilename, const std::string &userAcc)
    : resultJsonFilename(resultJsonFilename), username(userAcc)
{
    logFileFilename = logFilename;
}

ProcManipulationAggregator::ProcManipulationAggregator(const ProcManipulationAggregator &other)
{
    logFileFilename = other.logFileFilename;
    resultJsonFilename = other.resultJsonFilename;
}

ProcManipulationAggregator::~ProcManipulationAggregator()
{

}

void ProcManipulationAggregator::getInformationFromLogs()
{
    jsonLogRepresentation = getJsonData(resultJsonFilename);

    std::ifstream fin;
    fin.open(logFileFilename);
    if(fin.is_open() == false)
    {
        throw SIEM_errors::SIEMException("Cannot open file: " + logFileFilename);
    }

    std::string usersNodePath = constructPath(SLASH, 2, ROOT, USERS);
    jsonLogRepresentation.addOrUpdateNode(USERS, usersNodePath);

    std::string particularUserPath = constructPath(SLASH, 3, ROOT, USERS, username.c_str());

    std::string readFromFileStr;
    while(std::getline(std::cin, readFromFileStr))
    {
        std::list<std::string> parsedStr = parse_by_delimeter(readFromFileStr, " ");

        std::list<std::string>::iterator commandIter = std::next(parsedStr.begin(), 0);
        std::list<std::string>::iterator argsIter = std::next(parsedStr.begin(), 1);

        std::string argsStr;
        for(; argsIter != parsedStr.end(); argsIter++)
        {
            argsStr += (*argsIter + " ");
        }
        if(argsStr.length() > 0)
            argsStr.pop_back();     // Delete last space if exists

        std::string commandPath = constructPath(SLASH, 4, ROOT, USERS, username.c_str(), (*commandIter).c_str());
        jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(*commandIter, argsStr), commandPath);
    }

    fin.close();

    std::ofstream fout(logFileFilename, std::ios_base::trunc);
    jsonLogRepresentation.setJson(fout);
    fout.close();
}
