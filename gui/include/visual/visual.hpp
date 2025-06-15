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

enum VisualType_e {
    ENTITY = 0,
    INTERACTIVE,
    DRAWABLE,
    TEXT,
    OBJECT,
    ANIMATED,
    // TEXT_FIELD,
    // BUTTON
};

static const std::map<VisualType_e, std::vector<VisualType_e>> VISUAL_INHERITANCE = {
    {ENTITY, {}},
    {DRAWABLE, {ENTITY}},
    {INTERACTIVE, {ENTITY}},
    {TEXT, {ENTITY, DRAWABLE}},
    {OBJECT, {ENTITY, DRAWABLE}},
    {ANIMATED, {ENTITY, DRAWABLE, OBJECT}},
    // {TEXT_FIELD, {ENTITY, INTERACTIVE}},
    // {BUTTON, {ENTITY, INTERACTIVE}}
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
    GRASS = 0,
    SAND,
    SEA
};

struct TileInfo_s {
    BiomeTypes_e type;
    std::array<bool, NB_RESOURCES> resources;
};

static const std::vector<std::vector<TileInfo_s>> TEST_MAP = {
    {{GRASS, {1,1,0,0,0,0}}, {{GRASS}, {1,0,0,0,0,0}}, {{GRASS}, {1,0,0,0,0,0}}, {{GRASS}, {0,1,0,0,0,0}}, {{GRASS}, {1,0,0,0,0,0}}},
    {{SAND, {0,0,0,0,0,0}}, {{SAND}, {0,0,0,0,0,0}}, {{SAND}, {1,0,0,0,0,0}}, {{GRASS}, {0,1,0,0,0,0}}, {{GRASS}, {1,0,0,0,0,0}}},
    {{SEA, {0,0,0,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}, {{SAND}, {0,0,1,0,0,0}}, {{SAND}, {0,1,0,0,0,0}}, {{SAND}, {0,0,0,0,0,0}}},
    {{SAND, {0,0,1,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}, {{SAND}, {0,0,1,0,0,0}}},
    {{GRASS, {1,0,0,0,0,0}}, {{SAND}, {0,0,1,0,0,0}}, {{SAND}, {0,0,1,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}, {{SEA}, {0,0,0,0,0,0}}}
};

} // visual
} // gui

#endif