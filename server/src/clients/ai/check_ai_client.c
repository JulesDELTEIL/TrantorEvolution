/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** check_player.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "commands.h"
#include "actions.h"
#include "debug.h"
#include "functions.h"
#include "transmission.h"

static int buffer_handler(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (client == NULL || client->buffin == NULL)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_buffer(client);
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_COMMANDS[client->type]; k++)
        if (strcmp(cmd, COMMANDS[client->type][k].command) == 0)
            return COMMANDS[client->type][k].handler(sdata,
                fdarray, client, data);
    set_message(client, "ko", NULL, sdata->debug);
    return EXIT_FAILURE;
}

static int destroy_action(player_t *player)
{
    if (player->action.cmd != NULL)
        free(player->action.cmd);
    if (player->action.data != NULL)
        free(player->action.data);
    player->action.cmd = NULL;
    player->action.data = NULL;
    player->action.end = 0;
    player->action.status = DONE;
}

static int action_handler(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    int rc = DEFAULTRC;

    if (client->player->action.cmd == NULL)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_ACTIONS; k++) {
        if (strcmp(ACTIONS_ARR[k].name, client->player->action.cmd) == 0) {
            rc = ACTIONS_ARR[k].handler(sdata, fdarray, client,
                client->player->action.data);
            destroy_action(client->player);
            return rc;
        }
    }
}

static int buff_max_idx(client_t *client)
{
    uint_t nbcmd = 0;

    for (uint_t k = 0; client->buffin[k] != 0; k++) {
        if (client->buffin[k] == '\n')
            nbcmd++;
        if (nbcmd >= 10)
            return k;
    }
    return -1;
}

static int cap_player_buff(client_t *client)
{
    int buffmax_idx = 0;
    char *newbuff = NULL;

    if (client->buffin == NULL || client->buffin_addition == false)
        return EXIT_FAILURE;
    buffmax_idx = buff_max_idx(client);
    if (buffmax_idx != -1) {
        newbuff = malloc(sizeof(char) * (buffmax_idx + 1));
        for (uint_t k = 0; k < buffmax_idx; k++)
            newbuff[k] = client->buffin[k];
        newbuff[buffmax_idx] = 0;
        free(client->buffin);
        client->buffin = newbuff;
    }
    client->buffin_addition = false;
    return EXIT_SUCCESS;
}

static int check_player_timer(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    if ((tp.tv_sec * 1000 + tp.tv_usec / 1000) >= client->player->action.end)
        return action_handler(sdata, fdarray, client);
    return EXIT_FAILURE;
}

static int check_player_life(serverdata_t *sdata, client_t *client)
{
    struct timeval tp;
    size_t timenow = 0;

    gettimeofday(&tp, NULL);
    timenow = (tp.tv_sec * 1000 + tp.tv_usec / 1000);
    if (timenow >= client->player->time_use_life) {
        client->player->inventory[FOOD] -= 1;
        client->player->time_use_life = set_timer_end(sdata->args->freq,
            TICKS_FOOD_USE);
        if (client->player->inventory[FOOD] <= 0) {
            kill_player(sdata, client);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int check_ai_client(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    if (client->player == NULL)
        return EXIT_FAILURE;
    if (check_player_life(sdata, client) == EXIT_SUCCESS) {
        if (client->player->action.status != ONGOING)
            return buffer_handler(sdata, fdarray, client);
        else
            return check_player_timer(sdata, fdarray, client);
    }
}
