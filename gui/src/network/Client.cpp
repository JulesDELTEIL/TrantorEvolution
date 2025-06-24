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

void Client::pushNetpackEvent(const std::string& command)
{
    std::vector<char> tempV = _buffer;
    size_t k = command.size();
    Command infos = splitCodeAndArg(command);
    NetEventPack event;

    _buffer.clear();
    for (size_t i = k + 1; i < tempV.size(); ++i)
        _buffer.push_back(tempV[i]);
    if (CODE_EVENT_LINK.contains(infos.first)) {
        event.event = CODE_EVENT_LINK.at(infos.first);
        event.pack = infos.second;
        _events.push(event);
    }
}

void Client::checkEvent(void)
{
    int rc = 0;
    std::string command;

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
        for (size_t size = 0; _buffer[size] != '\n'; ++size) {
            if (size >= _buffer.size()) {
                command.clear();
                break;
            }
            command.push_back(_buffer[size]);
        }
        if (!command.empty()) {
            pushNetpackEvent(command);
            command.clear();
        }
    }
}

bool Client::pollEvent(NetEventPack& event)
{
    event.event = network::NONE;
    event.pack = {};
    if (_events.empty())
        return false;
    event = _events.front();
    _events.pop();
    return true;
}

void Client::sendData(const std::string& msg) const
{
    std::string to_send(msg);
    to_send.append("\n");
    write(_socket.getFd(), to_send.data(), to_send.size());
}
} // namespace network
} // namespace gui
