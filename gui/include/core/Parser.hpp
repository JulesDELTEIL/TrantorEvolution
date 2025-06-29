/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser.hpp
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <cstdint>
    #include <string>

namespace gui {
namespace core {

class Parser {
    public:
        Parser() = default;
        Parser(int argc, const char *argv[]);
        ~Parser() = default;

        uint32_t getPortNb() const;
        std::string getHostName() const;
        bool isUnsignedNumber(const std::string&) const;

        class Error;
        
    private:
        uint32_t _port_nb;
        std::string _host_name;
};

class Parser::Error : public std::exception
{
    public :
        Error() = default;
        Error(std::string ErrorType)
        {
            this->_ErrorType = ErrorType;
        }
        const char *what() const noexcept override
        {
            return _ErrorType.c_str();
        }
    private :
        std::string _ErrorType = "";
};

static const uint8_t ARGS_NB = 5;
static const uint8_t LAST_ARG = 4;

} // gui
} // core

#endif