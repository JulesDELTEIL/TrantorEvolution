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

namespace gui {
namespace visual {

enum Scene_e {
    NONE = 0,
    MENU,
    LOBBY,
    IN_GAME,
};

enum VisualType_e {
    ENTITY = 0,
    INTERACTIVE,
    DRAWABLE,
    TEXT,
    OBJECT,
    ANIMATED,
    TEXT_FIELD,
    BUTTON
};

static const std::map<VisualType_e, std::vector<VisualType_e>> VISUAL_INHERITANCE = {
    {ENTITY, {}},
    {DRAWABLE, {ENTITY}},
    {INTERACTIVE, {ENTITY}},
    {TEXT, {ENTITY, DRAWABLE}},
    {OBJECT, {ENTITY, DRAWABLE}},
    {ANIMATED, {ENTITY, DRAWABLE, OBJECT}},
    {TEXT_FIELD, {ENTITY, INTERACTIVE}},
    {BUTTON, {ENTITY, INTERACTIVE}}
};

enum BiomeTypes_e {
    GRASS = 0,
    SAND,
    SEA
};

enum ResourceType_e {
    WOOD = 0,
    STONE,
    CLAY,
    METAL,
    OIL,
    ANTI_MATTER
};

} // visual
} // gui

#endif