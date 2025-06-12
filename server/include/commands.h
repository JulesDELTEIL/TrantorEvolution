/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "structs.h"

enum alpha_ascii_e {
    A = 97,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

static const char CYE[3] = "cye"; //connection yes
static const char CNO[3] = "cno"; //connection no
static const char WRC[3] = "wrc"; //wrong command

int command_handler(serverdata_t *sdata, client_t *client, char *command);

typedef int (*handler_t)(serverdata_t *sdata, client_t *client);

typedef struct command_s {
    char command[3];
    int (*handler)(serverdata_t *sdata, client_t *client, uint cmd_idx);
    uint datalen;
} command_t;

int cmd_idn(serverdata_t *sdata, client_t *client, uint cmd_idx);

static const command_t USER_COMMANDS[] = {
    {"idn", &cmd_idn, 1 + EOP_LEN},
};

static const int NB_USER_COMMANDS = sizeof(USER_COMMANDS) / sizeof(command_t);

#endif
