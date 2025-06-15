/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

static suseconds_t get_action_end(int freq, int ticks)
{
    float delay = ((float)ticks / (float)freq) * 1000;
    struct timeval tp;
    size_t res = 0;

    gettimeofday(&tp, NULL);
    res = (tp.tv_sec * 1000 + tp.tv_usec / 1000) + (size_t)delay;
    printf("delay = %ld\n", res);
    return res;
}

int cmd_msz(serverdata_t *sdata, client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, "msz", answer);
    client->action_end = get_action_end(sdata->args->freq, 7);
    return EXIT_SUCCESS;
}
