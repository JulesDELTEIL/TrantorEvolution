/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser.cpp
*/

#include "core/Parser.hpp"
#include <string>
#include <iostream>

gui::core::Parser::Parser(int argc, const char *argv[])
{
    if (argc < ARGS_NB)
        throw gui::core::Parser::Error("Error: Wrong number of arguments");
    if (!isUnsignedNumber(argv[PORT_NB_ARG_INDEX]))
        throw gui::core::Parser::Error("Error: First argument should be an unsigned number");
    _port_nb = std::stoi(argv[PORT_NB_ARG_INDEX]);
    _host_name = argv[HOST_NAME_ARG_INDEX];
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
