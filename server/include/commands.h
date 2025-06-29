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
Sets the timeout end timer of the client depending on FREQ and TICKS
*/
size_t set_timer_end(int freq, int ticks);

/*
Sends pnw code of PLAYER to UI_CLIENT
*/
int send_pnw(serverdata_t *sdata, player_t *player, client_t *ui_client);

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
int cmd_look(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_eject(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_incantation(serverdata_t *, fdarray_t *, client_t *, char *);

int cmd_tna(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_msz(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_bct(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_mct(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_ppo(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_pin(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_plv(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_sgt(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_sst(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_pnw(serverdata_t *, fdarray_t *, client_t *, char *);
int cmd_bio(serverdata_t *, fdarray_t *, client_t *, char *);


static const command_t GUI_COMMANDS[] = {
    {"tna", cmd_tna},
    {"msz", cmd_msz},
    {"bct", cmd_bct},
    {"mct", cmd_mct},
    {"ppo", cmd_ppo},
    {"plv", cmd_plv},
    {"pin", cmd_pin},
    {"sgt", cmd_sgt},
    {"sst", cmd_sst},
    {"bio", cmd_bio},
    {"pnw", cmd_pnw}
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
    {"Look", cmd_look},
    {"Eject", cmd_eject},
    {"Incantation", cmd_incantation},
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
