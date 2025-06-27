/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** threads.h
*/

#ifndef THREADS_H_
    #define THREADS_H_

typedef struct serverdata_s serverdata_t;
typedef struct fdarray_s fdarray_t;

typedef struct thread_arg_t_s {
    fdarray_t *fdarray;
    serverdata_t *sdata;
} thread_arg_t;

#endif
