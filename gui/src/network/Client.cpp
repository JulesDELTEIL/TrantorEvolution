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

Client::~Client()
{
    _network_runing = false;
    _network.join();
}

static Command splitCodeAndArg(const std::string &string)
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
    _network_runing = true;
    _network = std::thread(&Client::checkEvent, this);
}

void Client::checkEvent(void)
{
    int rc = 0;

    while (_network_runing) {
        _socket.pollServer();
        if (_socket.fds().revents & POLLIN) {
            char tempBuffer[BUFSIZ] = {0};
            rc = read(_socket.getFd(), tempBuffer, BUFSIZ);
            if (rc > 0) {
                for (int k = 0; k < rc; k++)
                    _buffer.push_back(tempBuffer[k]);
            }
        }
    }
}

bool Client::pollEvent(NetEventPack& event)
{
    size_t size = _buffer.size();
    std::vector<char> tempV = _buffer;
    size_t k = 0;
    std::string command;

    event.event = network::NONE;
    event.pack = {};
    if (size == 0)
        return false;
    for (k = 0; _buffer[k] != '\n'; ++k)
        command.push_back(_buffer[k]);
    _buffer.clear();
    for (size_t i = k + 1; i < tempV.size(); i++)
        _buffer.push_back(tempV[i]);
    Command infos = splitCodeAndArg(command);
    if (CODE_EVENT_LINK.contains(infos.first)) {
        event.event = CODE_EVENT_LINK.at(infos.first);
        event.pack = infos.second;
        return true;
    }
    return false;
}

void Client::sendData(const std::string& msg) const
{
    write(_socket.getFd(), msg.data(), msg.size());
}

} // namespace network
} // namespace gui
