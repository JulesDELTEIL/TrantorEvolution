/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include "network/events.hpp"
    #include "network/Socket.hpp"

namespace gui {
namespace network {

class Client {
    public:
        Client() = default;
        ~Client() = default;

        void checkEvent(void);
        void setSocket(const std::string &server, const int &port);
        bool pollEvent(NetEventPack&);

    private:
        Socket _socket;
        PackQueue _events;

};

} // namespace network
} // namespace gui

#endif
