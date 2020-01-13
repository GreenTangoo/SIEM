#include "handler.hpp"

SIEM_errors::hander_error::hander_error(const char *str)
{
    error_msg = std::string(str);
}

SIEM_errors::hander_error::hander_error(const std::string &str)
{
    error_msg = str;
}

SIEM_errors::hander_error::~hander_error() noexcept
{

}

const char* SIEM_errors::hander_error::what() const noexcept
{
    return error_msg.c_str();
}
