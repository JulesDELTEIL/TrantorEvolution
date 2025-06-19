/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.cpp
*/

#include <unistd.h> 
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "network/Client.hpp"

namespace gui {
namespace network {

static Command splitCodeAndArg
    (const std::string &string)
{
    std::string temp;
    std::string code;
    NetPack arg;
    std::stringstream line(string);

    line >> code;
    while(!line.eof()) {
        line >> temp;
        arg.push_back(temp);
    }
    return std::make_pair(code, arg);
}

void Client::setSocket(const std::string &server, const int &port)
{
    _socket.setSocket(server, port);
    _stream.reset(fdopen(_socket.getFd(), "r"));
}

void Client::checkEvent(void)
{
    char *buffer;
    size_t len = BUFF_SIZE;
    Command command;

    _socket.pollServer();
    if (_socket.fds().revents & POLLIN) {
        getline(&buffer, &len, _stream.get());
        command = splitCodeAndArg(buffer);
        if (CODE_EVENT_LINK.contains(command.first)) {
            _events.push({CODE_EVENT_LINK.at(command.first), command.second});
        }
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
