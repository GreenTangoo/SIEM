#include "iptables_aggr.hpp"

using namespace aggregator_space;
using namespace parser_string_space;

#define ROOT "root"
#define IPTABLES "iptables"
#define DESTINATION_IP "dst-ip"
#define AMOUNT_REQ "amount-requests"

IptablesAggregator::IptablesAggregator(const std::string &logFilename, const std::string &resultJsonFilename) : resultJsonFilename(resultJsonFilename)
{
    logFileFilename = logFilename;
}

IptablesAggregator::IptablesAggregator(const IptablesAggregator &other)
{
    logFileFilename = other.logFileFilename;
    jsonLogRepresentation = other.jsonLogRepresentation;
}

IptablesAggregator::~IptablesAggregator()
{

}

void IptablesAggregator::getInformationFromLogs()
{
    jsonLogRepresentation = getJsonData(resultJsonFilename);

    std::ifstream fin;
    fin.open(logFileFilename);
    if(fin.is_open() == false)
    {
        throw SIEM_errors::SIEMException("Cannot open file: " + logFileFilename);
    }

    std::string iptablesMainNodePath = constructPath(SLASH, 2, ROOT, IPTABLES);
    jsonLogRepresentation.addOrUpdateNode(IPTABLES, iptablesMainNodePath.c_str());

    std::map<std::string, int> amountRequestsFromOneIp;

    std::string oneLine;
    while(std::getline(fin, oneLine))
    {
        std::list<std::string> parsedStringFromConf = parse_by_delimeter(oneLine, " ");
        std::list<std::string>::iterator srcIpIter = std::next(parsedStringFromConf.begin(), 10);
        std::string ipSrcAddr = srcIpIter->substr(4);

        std::string ipSrcNodePath = constructPath(SLASH, 3, ROOT, IPTABLES, ipSrcAddr.c_str());
        jsonLogRepresentation.addOrUpdateNode(ipSrcAddr, ipSrcNodePath);

        amountRequestsFromOneIp[ipSrcAddr]++;

        std::list<std::string>::iterator dstIpIter = std::next(parsedStringFromConf.begin(), 11);
        std::string ipDstAddr = dstIpIter->substr(4);

        std::string ipDstNodePath = constructPath(SLASH, 4, ROOT, IPTABLES, ipSrcAddr.c_str(), DESTINATION_IP);
        jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(DESTINATION_IP, ipDstAddr), ipDstNodePath);

        int amountReq = amountRequestsFromOneIp[ipSrcAddr];

        std::string amountReqNodePath = constructPath(SLASH, 4, ROOT, IPTABLES, ipSrcAddr.c_str(), AMOUNT_REQ);
        jsonLogRepresentation.addOrUpdateString(std::pair<std::string, std::string>(AMOUNT_REQ, std::to_string(amountReq)), amountReqNodePath);

    }

    fin.close();

    std::ofstream fout(resultJsonFilename, std::ios_base::trunc);
    jsonLogRepresentation.setJson(fout);
    fout.close();
}

