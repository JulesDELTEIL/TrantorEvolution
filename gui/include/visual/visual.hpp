/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** visual.hpp
*/

#ifndef VISUAL_HPP_
    #define VISUAL_HPP_

    #include <map>
    #include <vector>
    #include <array>

namespace gui {
namespace visual {

enum Scene_e {
    NONE = 0,
    MENU,
    LOBBY,
    IN_GAME,
};

enum ResourceType_e {
    WOOD = 0,
    STONE,
    CLAY,
    METAL,
    OIL,
    ANTI_MATTER
};

    #define NB_RESOURCES 6

/*  Tile  */
enum BiomeTypes_e {
    EMPTY = 0,
    GRASS,
    SAND,
    SEA
};

} // visual
} // gui

#endif