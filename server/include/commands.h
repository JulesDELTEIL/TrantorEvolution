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
int buffer_handler(serverdata_t *sdata, client_t *client);

/*
Sets the timeout end timer of the client depending on FREQ and TICKS
*/
void set_action_end(client_t *client, int freq, int ticks);

/*
Command structure designed for the function pointer array by matching the char *COMMAND

struct command_t :
- char *command (command name)
- int *handler(serverdata_t *sdata, client_t *client, char *data) (handler function pointer)
*/
typedef struct command_s {
    char *command;
    int (*handler)(serverdata_t *sdata, client_t *client, char *data);
} command_t;

int cmd_tna(serverdata_t *sdata, client_t *client, char *data);
int cmd_idn(serverdata_t *sdata, client_t *client, char *data);
int cmd_msz(serverdata_t *sdata, client_t *client, char *data);

static const command_t USER_COMMANDS[] = {
    {"tna", &cmd_tna},
    {"idn", &cmd_idn},
    {"msz", &cmd_msz}
};

static const int NB_USER_COMMANDS = sizeof(USER_COMMANDS) / sizeof(command_t);

#endif
