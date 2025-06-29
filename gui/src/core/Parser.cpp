/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser.cpp
*/

#include "core/Parser.hpp"
#include <string>
#include <iostream>
#include <cstring>

gui::core::Parser::Parser(int argc, const char *argv[])
{
    std::string port_str;

    if (argc < ARGS_NB)
        throw gui::core::Parser::Error("Error: Wrong number of arguments");
    for (int i = 0; i < ARGS_NB; i++) {
        if (strcmp(argv[i], "-h") == 0 && i != LAST_ARG)
            _host_name = std::string(argv[i + 1]);
        if (strcmp(argv[i], "-p") == 0 && i != LAST_ARG)
            port_str = std::string(argv[i + 1]);
    }
    if (port_str.empty() || _host_name.empty())
        throw gui::core::Parser::Error("Error: Missing argument");
    if (!isUnsignedNumber(port_str))
        throw gui::core::Parser::Error("Error: Port is not an unsigned integer");
    _port_nb = std::stoi(port_str);
    if (_port_nb < 1025)
        throw gui::core::Parser::Error("Error: Port number is lesser than 1025");
}

uint32_t gui::core::Parser::getPortNb(void) const
{
    return _port_nb;
}

std::string gui::core::Parser::getHostName(void) const
{
    return _host_name;
}

bool gui::core::Parser::isUnsignedNumber(const std::string& string) const
{
    for (const auto& it : string)
        if (!isdigit(it))
            return false;
    return true;
}
