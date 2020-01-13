#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <exception>
#include <string>

namespace SIEM_errors
{
    class hander_error : std::exception
    {
    protected:
        std::string error_msg;
    public:
        explicit hander_error(const char *str);
        explicit hander_error(const std::string &str);
        virtual ~hander_error() noexcept;
        virtual const char* what() const noexcept;
    };
}

#endif
