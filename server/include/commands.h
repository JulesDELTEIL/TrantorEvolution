/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "serverdata.h"
    #include "fdarray.h"

/*
Function called to handle the first valid command found in the client buffer
*/
int buffer_handler(serverdata_t *sdata, fdarray_t *fdarray, client_t *client);

/*
Sets the timeout end timer of the client depending on FREQ and TICKS
*/
void set_action_end(client_t *client, int freq, int ticks);

/*
Command structure designed for the function pointer array by
    matching the char *COMMAND

struct command_t :
- char *command (command name)
- int *handler(serverdata_t *, fdarray_t *, client_t *, char *)
    (handler function pointer)
*/
typedef struct command_s {
    char *command;
    int (*handler)(serverdata_t *, fdarray_t *, client_t *, char *);
} command_t;

int cmd_forward(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_fork(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_left(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_right(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_inventory(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_take(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_set(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_connect_nbr(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_broadcast(serverdata_t *, fdarray_t *, client_t *, char *);

int cmd_tna(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_msz(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_bct(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_mct(serverdata_t *, fdarray_t *, client_t *, char *);

static const command_t GUI_COMMANDS[] = {
    {"tna", cmd_tna},
    {"msz", cmd_msz},
    {"bct", cmd_bct},
    {"mct", cmd_mct}
};

static const command_t AI_COMMANDS[] = {
    {"Forward", cmd_forward},
    {"Left", cmd_left},
    {"Right", cmd_right},
    {"Fork", cmd_fork},
    {"Inventory", cmd_inventory},
    {"Take", cmd_take},
    {"Set", cmd_set},
    {"Connect_nbr", cmd_connect_nbr},
    {"Broadcast", cmd_broadcast},
};

static const command_t *COMMANDS[] = {
    AI_COMMANDS,
    GUI_COMMANDS
};

static const int NB_COMMANDS[] = {
    sizeof(AI_COMMANDS) / sizeof(command_t),
    sizeof(GUI_COMMANDS) / sizeof(command_t)
};

#endif
