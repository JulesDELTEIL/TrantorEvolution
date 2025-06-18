/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** events.cpp
*/

#include "network/events.hpp"

namespace gui {
namespace network {

NetType::NetType(const std::string& value)
: _value(value) {}

size_t NetType::getSize_t(void) const
{
    return std::stoi(_value);
}

float NetType::getFloat(void) const
{
    return std::stol(_value);
}

int NetType::getInt(void) const
{
    return std::stof(_value);
}

std::string NetType::getString(void) const
{
    return _value;
}

} // namespace newtork
} // namespace gui
