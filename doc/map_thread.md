# Server Gameplay / Map Thread Overview

In this project, one crucial component is the map system and how it is managed during gameplay.
Many mechanics depend on it working correctly from resource generation to biome behavior.

This page covers:

 - Error handling during map initialization

- Resource densities and biome distribution

- The dedicated thread responsible for managing map refills and biome logic

## Error Handling

The map is initialized using the zappy_server command-line arguments:

./zappy_server -p <port> -x <width max 100> -y <height max 100> -n <team1 team2 ...> -c <clientsNb> -f <freq> [-d]

 - -x and -y define the width and height of the map, respectively.

 - These dimensions must be at least *5* and must not exceed *100*.

Once validated, the server allocates and initializes a 2D map composed of map_t structures:
```c
typedef struct map_s {
    unsigned int resources[NB_RESOURCES];
    unsigned int biome;
} map_t;
```

NB_RESOURCES defines the available resource types:
```c
enum ressources_e {
    FOOD,
    WOOD,
    ROCK,
    CLAY,
    METAL,
    PETROL,
    ANTIMATTER
};
```

Each tile also receives a biome, chosen randomly from the following:
```c
enum biome_e {
    SEA,
    FOREST,
    MOUNTAINS,
    PLAINS,
    BEACH
};
```
## Resource Densities

The total amount of each resource on the map is limited by a density factor:

- MAX_QUANTITY = MAP_WIDTH * MAP_HEIGHT * RESOURCE_DENSITY

Defined densities for each resource:
```c
#define FOOD_DENSITY 0.5
#define WOOD_DENSITY 0.3
#define ROCK_DENSITY 0.15
#define CLAY_DENSITY 0.1
#define METAL_DENSITY 0.1
#define PETROL_DENSITY 0.08
#define ANTIMATTER_DENSITY 0.05
```
These limits are enforced at refill time, meaning no resource can exceed its global density.
Biomes and Distribution

Each tile is assigned a biome upon initialization,
influencing both its initial resources and future refills.

Biome Refill Distributions:

- Mountains → 50% Rock, 20% Wood, 20% Metal, 10% Antimatter

- Forest → 70% Wood, 10% Rock, 20% Antimatter

- Plains → 60% Clay, 10% Wood, 10% Rock, 10% Metal, 10% Antimatter

- Beach → 50% Petrol, 30% Clay, 10% Metal, 10% Antimatter

- Sea → 50% Petrol, 20% Clay, 10% Wood, 20% Antimatter

Note: Every tile always starts with 3 units of FOOD, regardless of biome.

These distributions are defined in a biome_distributions[] constant array and are used both for initial placement and refills.

## Map Thread & Refill System

A dedicated thread is responsible for the dynamic behavior of the map during the game:

- Every 20 seconds, the thread iterates through all tiles.

- For each tile, it attempts to refill resources based on:

    - Its biome-specific distribution

    - The global maximum density of each resource

- A tile never adds more of a resource if that resource has already reached its global density.

Example logic (simplified):
```c
void *map_thread(void *arg) {
    while (server_is_running) {
        refill_map(server->game_data.map, width, height, &max_density);
        sleep(20);
    }
}
```
The refill logic uses flattened indexing
(x = i / height; y = i % height;) and avoids exceeding density,
replacing traditional if statements with ternary expressions when possible
due to the hardly but worthy epitech coding style.