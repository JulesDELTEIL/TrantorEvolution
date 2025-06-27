/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** serverdata.h
*/

#ifndef SERVERDATA_H_
    #define SERVERDATA_H_

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <stdbool.h>
    #include "macros.h"
    #include "game.h"

/*
struct serverdata_t :
- int port
- int sockfd
- struct sockaddr_in address
- socklen_t addrlen
- int opt
- bool debug
- arguments_t *args
- map_t trantor_map all the tiles of the map
*/
typedef struct serverdata_s {
    int port;
    int sockfd;
    int opt;
    socklen_t addrlen;
    struct sockaddr_in address;
    arguments_t *args;
    game_t game_data;
    bool debug;
    bool is_running;
} serverdata_t;

#endif
