/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** visual.hpp
*/

#ifndef VISUAL_HPP_
    #define VISUAL_HPP_

namespace gui {
namespace visual {

enum Scene_e {
    NONE = 0,
    MENU,
    LOBBY,
    IN_GAME,
};

enum resource_e {
    FOOD = 0,
    WOOD,
    STONE,
    CLAY,
    METAL,
    OIL,
    ANTI_MATTER
};

typedef std::map<resource_e, size_t> ResourceGroup;

} // visual
} // gui

#endif