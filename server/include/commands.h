/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "serverdata.h"
    #include "fdarray.h"

int buffer_handler(serverdata_t *sdata, client_t *client);

void set_action_end(client_t *client, int freq, int ticks);

typedef int (*handler_t)(serverdata_t *sdata, client_t *client);

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
