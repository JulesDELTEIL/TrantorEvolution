/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Socket.hpp
*/

#ifndef SOCKET_HPP_
    #define SOCKET_HPP_

    #include <string>

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <poll.h>


namespace gui {
namespace network {

class Socket {
  public:
    class socketError : public std::exception {
      public:
        socketError(const std::string& msg) {errorMessage = "Error Socket: " + msg;};
        const char *what() const noexcept {return errorMessage.c_str();};

      private:
          std::string errorMessage;
    };
    Socket() = default;
    ~Socket();

    void setSocket(const std::string& server, const int& port);
    void pollServer(void);
    struct pollfd fds(void) const; 

    int getFd(void) const;

  private:
    struct pollfd _fds;
    struct sockaddr_in _servadr;
};

} // network
} // gui

#endif