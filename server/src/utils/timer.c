/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** timer.c
*/

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

size_t set_timer_end(int freq, int ticks)
{
    float delay = ((float)ticks / (float)freq) * 1000;
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return (size_t)(tp.tv_sec * 1000 + tp.tv_usec / 1000) + (size_t)delay;
}
