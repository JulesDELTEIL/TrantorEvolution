/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.cpp
*/

#include "network/Client.hpp"

namespace gui {
namespace network {

void Client::checkEvent(void)
{
    _socket.pollServer();
    if (_socket.fds().revents & POLLIN) {
        _events.push(NET_MSIZE); // TEST
    }
}

bool Client::pollEvent(NetEvent_e& event)
{
    if (_events.size() > 0) {
        event = _events.front();
        _events.pop();
        return true;
    } else 
        return false;
}

} // namespace network
} // namespace gui
