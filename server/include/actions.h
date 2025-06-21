/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** actions.h
*/

#ifndef ACTIONS_H_
    #define ACTIONS_H_

    #include "serverdata.h"
    #include "fdarray.h"

/*
Function called to handle the first valid command found in the client buffer
*/
int buffer_handler(serverdata_t *sdata, fdarray_t *fdarray, client_t *client);

/*
Command structure designed for the function pointer array by
    matching the char *ACTION

struct action_t :
- char *name (command name)
- int *handler(serverdata_t *, fdarray_t *, client_t *, char *)
    (handler function pointer)
*/
typedef struct action_handler_s {
    char *name;
    int (*handler)(serverdata_t *, fdarray_t *, client_t *, char *);
} action_handler_t;

int action_forward(serverdata_t *, fdarray_t *, client_t *, char *);
int action_fork(serverdata_t *, fdarray_t *, client_t *, char *);
int action_left(serverdata_t *, fdarray_t *, client_t *, char *);
int action_right(serverdata_t *, fdarray_t *, client_t *, char *);
int action_inventory(serverdata_t *, fdarray_t *, client_t *, char *);
int action_take(serverdata_t *, fdarray_t *, client_t *, char *);
int action_set(serverdata_t *, fdarray_t *, client_t *, char *);
int action_connect_nbr(serverdata_t *, fdarray_t *, client_t *, char *);
int action_broadcast(serverdata_t *, fdarray_t *, client_t *, char *);

enum actions_e {
    FORWARD = 0,
    LEFT,
    RIGHT,
    FORK,
    INVENTORY,
    TAKE,
    SET,
    CONNECT_NBR,
    BROADCAST
};

static const action_handler_t ACTIONS_ARR[] = {
    {"Forward", action_forward},
    {"Left", action_left},
    {"Right", action_right},
    {"Fork", action_fork},
    {"Inventory", action_inventory},
    {"Take", action_take},
    {"Set", action_set},
    {"Connect_nbr", action_connect_nbr},
    {"Broadcast", action_broadcast},
};

static const int NB_ACTIONS = sizeof(ACTIONS_ARR) / sizeof(action_handler_t);

#endif
