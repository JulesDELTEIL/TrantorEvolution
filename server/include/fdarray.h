/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** fdarray.h
*/

#ifndef FDARRAY_H_
    #define FDARRAY_H_

    #include <poll.h>
    #include <stdlib.h>

    #include "macros.h"
    #include "items.h"
    #include "team.h"

    #define NB_DIFF_ITEMS 7

typedef enum player_dir_e {
    N = 1,
    E,
    S,
    W
} player_dir_t;

/*
struct player_t :
- size_t level
- uint_t x
- uint_t y
- uint_t orientation
*/
typedef struct player_s {
    int id;
    team_t *team;
    size_t level;
    uint_t x;
    uint_t y;
    player_dir_t orientation;
    uint_t inventory[NB_DIFF_ITEMS];
    struct player_s *next;
} player_t;

/*
struct client_t :
- int fd
- int id
- int type (if the client is ai or gui)
- char *team
- char *buffer (command buffer)
- size_t act_end (timestamp in ms of when the player
    will be able to do the next action)
- player_t player
*/
typedef struct client_s {
    int fd;
    int type;
    char *buffer;
    size_t act_end;
    player_t *player;
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
