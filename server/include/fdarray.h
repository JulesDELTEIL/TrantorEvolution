/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** structs.h
*/

#ifndef FDARRAY_H_
    #define FDARRAY_H_

    #include <poll.h>
    #include <stdlib.h>

    #include "macros.h"

/*
struct player_t :
- size_t level
- uint_t x
- uint_t y
- uint_t direction
*/
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
- int id
- int type (if the client is ai or gui)
- char *team
- char *buffer (command buffer)
- size_t act_end (timestamp in ms of when the player will be able to do the next action)
- player_t player
*/
typedef struct client_s {
    int fd;
    int id;
    int type;
    char *team;
    char *buffer;
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

#endif
