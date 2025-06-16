/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Socket.cpp
*/
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "network/Socket.hpp"

namespace gui {
namespace network {

Socket::Socket(const std::string& server, const std::string& port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    _servadr.sin_family = AF_INET;
    _servadr.sin_addr.s_addr = htons(INADDR_ANY);
    _servadr.sin_port = htons(std::stoi(port));
    if (inet_pton(AF_INET, server.c_str(), &_servadr.sin_addr) <= 0)
        throw socketError("IP not found, port might be wrong too");
    if (connect(fd, (struct sockaddr*)&_servadr, sizeof(_servadr)) < 0)
        throw socketError("connection failed");
    _fds.fd = fd;
    _fds.events = POLLIN;
}

Socket::~Socket()
{
    close(_fds.fd);
}

int Socket::getFd(void) const
{
    return _fds.fd;
}

void Socket::pollServer(void)
{
    poll(&_fds, 1, 0);
}

struct pollfd Socket::fds(void) const
{
    return _fds;
}

} // network
} // gui

