/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <memory>

    #include "network/events.hpp"
    #include "network/Socket.hpp"
    
    #define CODE_LEN 3
    #define BUFF_SIZE 1024

namespace gui {
namespace network {

class Client {
    public:
        Client() = default;
        ~Client() = default;

        void checkEvent(void);
        void setSocket(const std::string &server, const int &port);
        bool pollEvent(NetEventPack&);
        void sendData(const std::string& msg) const;

    private:
        Socket _socket;
        PackQueue _events;
        std::unique_ptr<FILE> _stream;

};

} // namespace network
} // namespace gui

#endif
