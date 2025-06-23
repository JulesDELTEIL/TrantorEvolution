/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** perlin
*/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "items.h"
#include "map.h"
#include "serverdata.h"

static int noise_hash(int x, int y, int *hash)
{
    int tmp = hash[y % HASH_SIZE];

    return hash[(tmp + x) % HASH_SIZE];
}

static float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}

static float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

static float noise_2d(float x, float y, int *hash)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise_hash(x_int, y_int, hash);
    int t = noise_hash(x_int + FOLLOWING_ONE, y_int, hash);
    int u = noise_hash(x_int, y_int + FOLLOWING_ONE, hash);
    int v = noise_hash(x_int + FOLLOWING_ONE, y_int + FOLLOWING_ONE, hash);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);

    return smooth_inter(low, high, y_frac);
}

static void init_hash(int *hash)
{
    int j = 0;
    int tmp = 0;

    srand(0);
    for (int i = 0; i < HASH_SIZE; i++)
        hash[i] = i;
    for (int i = HASH_SIZE - 1; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = hash[i];
        hash[i] = hash[j];
        hash[j] = tmp;
    }
}

float perlin_2d(float x, float y, float freq, int depth)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0.0;
    float div = 0.0;
    int hash[HASH_SIZE];

    init_hash(hash);
    for (int i = 0; i < depth; i++) {
        div += HASH_SIZE * amp;
        fin += noise_2d(xa, ya, hash) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin / div;
}
