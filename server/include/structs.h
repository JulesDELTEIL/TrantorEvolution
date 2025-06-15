/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** structs.h
*/

#ifndef SERVERSTRUCTS_H_
    #define SERVERSTRUCTS_H_

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <stdbool.h>
    #include <sys/time.h>

    #include "macros.h"

typedef struct player_s {
    size_t score;
    float pos_x;
    float pos_y;
    size_t meters;
    int speed;
    uint_t status;
} player_t;

/*
struct client_t :
- int fd
- char *user
- bool logged_in
*/
typedef struct client_s {
    int fd;
    int id;
    int type;
    char *team;
    char *buffer;
    uint_t cmd_nb;
    size_t act_end;
    player_t player;
} client_t;

/*
struct fdarray_t :
- client_t clients[NBTOTAL_FD]
 - struct pollfd fds[NBTOTAL_FD]
 */
typedef struct fdarray_s {
    client_t clients[NBTOTAL_FD];
    struct pollfd fds[NBTOTAL_FD];
} fdarray_t;

/*
struct arguments_t :
 - int port
 - int width of the map
 - int height of the map
 - int clientsNb
 - int freq reciprocal of time unit
 - char **teamName stocking the name of every team
 - bool debug
*/
typedef struct arguments_s {
    int port;
    int width;
    int height;
    int clientnb;
    int freq;
    char **team_name;
    bool debug;
} arguments_t;

/*
struct serverdata_t :
 - int port
 - int sockfd
 - struct sockaddr_in address
 - socklen_t addrlen
 - int opt
*/
typedef struct serverdata_s {
    int port;
    int sockfd;
    struct sockaddr_in address;
    socklen_t addrlen;
    int opt;
    arguments_t *args;
} serverdata_t;

#endif
