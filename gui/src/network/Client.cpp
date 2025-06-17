/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.cpp
*/

#include <unistd.h> 

#include "network/Client.hpp"

namespace gui {
namespace network {

void Client::setSocket(const std::string &server, const int &port)
{
    _socket.setSocket(server, port);
}

void Client::checkEvent(void)
{
    char buffer[CODE_LEN] = {0};

    _socket.pollServer();
    if (_socket.fds().revents & POLLIN) {
        read(_socket.getFd(), &buffer, CODE_LEN);
        _events.push({NET_MSIZE, {1, 2, 3}}); // TEST
    }
}

bool Client::pollEvent(NetEventPack& event)
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
