#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <exception>
#include <string>

namespace SIEM_errors
{
    class SIEMException : std::exception
    {
    protected:
        std::string error_msg;
    public:
        explicit SIEMException(const char *str);
        explicit SIEMException(const std::string &str);
        virtual ~SIEMException() noexcept;
        virtual const char* what() const noexcept;
    };
}

#endif
