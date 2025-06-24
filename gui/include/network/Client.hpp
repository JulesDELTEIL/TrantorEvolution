/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <memory>
    #include <thread>

    #include "network/events.hpp"
    #include "network/Socket.hpp"
    
    #define CODE_LEN 3
    #define BUFF_SIZE 1024

namespace gui {
namespace network {

class Client {
    public:
        Client() = default;
        ~Client();

        void checkEvent(void);
        void setSocket(const std::string &server, const int &port);
        bool pollEvent(NetEventPack&);
        void sendData(const std::string& msg) const;

    private:
        Socket _socket;
        std::unique_ptr<FILE> _stream;
        std::vector<char> _buffer;
        std::thread _network;
        bool _network_runing = false;
};

} // namespace network
} // namespace gui

#endif
