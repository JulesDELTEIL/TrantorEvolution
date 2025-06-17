/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** events.cpp
*/

#include "network/events.hpp"

gui::network::NetType::NetType(const std::string& value)
: _value(value) {}

size_t gui::network::NetType::getSize_t(void)
{
    return std::stoi(_value);
}

float gui::network::NetType::getFloat(void)
{
    return std::stol(_value);
}

int gui::network::NetType::getInt(void)
{
    return std::stof(_value);
}

std::string gui::network::NetType::getString(void)
{
    return _value;
}