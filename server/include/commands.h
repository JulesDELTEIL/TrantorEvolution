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
- int *handler(serverdata_t *sdata, client_t *client, char *data)
    (handler function pointer)
*/
typedef struct command_s {
    char *command;
    int (*handler)(serverdata_t *sdata, client_t *client, char *data);
} command_t;

int cmd_forward(serverdata_t *sdata, client_t *client, char *data);

int cmd_tna(serverdata_t *sdata, client_t *client, char *data);
int cmd_msz(serverdata_t *sdata, client_t *client, char *data);
int cmd_bct(serverdata_t *sdata, client_t *client, char *data);
int cmd_mct(serverdata_t *sdata, client_t *client, char *data);

static const command_t GUI_COMMANDS[] = {
    {"tna", &cmd_tna},
    {"msz", &cmd_msz},
    {"bct", &cmd_bct},
    {"mct", &cmd_mct}
};

static const command_t AI_COMMANDS[] = {
    {"Forward", &cmd_forward}
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
