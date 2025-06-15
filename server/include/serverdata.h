/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** structs.h
*/

#ifndef SERVERDATA_H_
    #define SERVERDATA_H_

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <stdbool.h>

    #include "macros.h"

/*
struct arguments_t :
- int port
- int width (width of the map)
- int height (height of the map)
- int clientsnb (number of authorized clients per team)
- int freq (reciprocal of time unit)
- char **team_name (name of every team in an array, null terminated)
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
- bool debug
- arguments_t *args
*/
typedef struct serverdata_s {
    int port;
    int sockfd;
    struct sockaddr_in address;
    socklen_t addrlen;
    int opt;
    bool debug;
    arguments_t *args;
} serverdata_t;

#endif
