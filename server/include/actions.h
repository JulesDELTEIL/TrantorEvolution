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
    unsigned int delay;
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
int action_look(serverdata_t *, fdarray_t *, client_t *, char *);
int action_eject(serverdata_t *, fdarray_t *, client_t *, char *);
int action_incantation(serverdata_t *, fdarray_t *, client_t *, char *);

enum actions_e {
    FORWARD = 0,
    LEFT,
    RIGHT,
    FORK,
    INVENTORY,
    TAKE,
    SET,
    CONNECT_NBR,
    BROADCAST,
    LOOK,
    EJECT,
    INCANTATION
};

static const action_handler_t ACTIONS_ARR[] = {
    {"Forward", action_forward, 7},
    {"Left", action_left, 7},
    {"Right", action_right, 7},
    {"Fork", action_fork, 42},
    {"Inventory", action_inventory, 1},
    {"Take", action_take, 7},
    {"Set", action_set, 7},
    {"Connect_nbr", action_connect_nbr, 0},
    {"Broadcast", action_broadcast, 7},
    {"Look", action_look, 7},
    {"Eject", action_eject, 7},
    {"Incantation", action_incantation, 300},
};

static const int NB_ACTIONS = sizeof(ACTIONS_ARR) / sizeof(action_handler_t);

#endif
