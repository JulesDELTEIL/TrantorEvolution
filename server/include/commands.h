/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "structs.h"

typedef int (*handler_t)(serverdata_t *sdata, client_t *client);

typedef struct command_s {
    uint8_t *command;
    int (*handler)(serverdata_t *sdata, client_t *client);
} command_t;

int command_handler(serverdata_t *sdata, client_t *client, uint8_t *command);

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

static const uint8_t CYE[3] = {C, Y, E}; //connection yes
static const uint8_t CNO[3] = {C, N, O}; //connection no
static const uint8_t WRC[3] = {W, R, C}; //wrong command

static const command_t user_commands[] = {
};

static const int NB_COMMANDS = sizeof(user_commands) / sizeof(command_t);

#endif
