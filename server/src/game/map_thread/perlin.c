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

static int noise_hash(int x, int y)
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

static float noise_2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise_hash(x_int, y_int);
    int t = noise_hash(x_int + FOLLOWING_ONE, y_int);
    int u = noise_hash(x_int, y_int + FOLLOWING_ONE);
    int v = noise_hash(x_int + FOLLOWING_ONE, y_int + FOLLOWING_ONE);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);

    return smooth_inter(low, high, y_frac);
}

float perlin_2d(float x, float y, float freq, int depth)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0.0;
    float div = 0.0;

    for (int i = 0; i < depth; i++) {
        div += HASH_SIZE * amp;
        fin += noise_2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin / div;
}
