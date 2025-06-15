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
    #include <stdbool.h>

    #include "macros.h"

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
