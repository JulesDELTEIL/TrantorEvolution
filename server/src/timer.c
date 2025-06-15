/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** timer.c
*/

#include <stdlib.h>
#include <sys/time.h>

#include "functions.h"

void set_action_end(client_t *client, int freq, int ticks)
{
    float delay = ((float)ticks / (float)freq) * 1000;
    struct timeval tp;

    gettimeofday(&tp, NULL);
    client->act_end = (tp.tv_sec * 1000 + tp.tv_usec / 1000) + (size_t)delay;
}
