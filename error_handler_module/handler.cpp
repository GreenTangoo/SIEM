#include "handler.hpp"

using namespace SIEM_errors;

SIEM_errors::SIEMException::SIEMException(const char *str)
{
    error_msg = std::string(str);
}

SIEM_errors::SIEMException::SIEMException(const std::string &str)
{
    error_msg = str;
}

SIEM_errors::SIEMException::~SIEMException() noexcept
{

}

const char* SIEM_errors::SIEMException::what() const noexcept
{
    return error_msg.c_str();
}
