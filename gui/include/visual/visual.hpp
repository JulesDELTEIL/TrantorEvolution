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
    MENU = 1,
    LOBBY = 2,
    IN_GAME = 3,
};

enum VisualType_e {
    DRAWABLE,
    INTERACTIVE,
    ANIMATED,
    TEXT,
    TEXT_FIELD,
    BUTTON,
    DRAG_DROP,
    DROP_DOWN,
    OBJECT,
    TRANTOR,
    MATERIALS,
    BACKGROUND,
};

static const std::map<VisualType_e, std::vector<VisualType_e>> INHERITANCE = {
    {DRAWABLE, {}},
    {INTERACTIVE, {DRAWABLE}},
    {ANIMATED, {DRAWABLE}},
    {TEXT, {DRAWABLE}},
    {TEXT_FIELD, {DRAWABLE, INTERACTIVE}},
    {BUTTON, {DRAWABLE, INTERACTIVE}},
    {DRAG_DROP, {DRAWABLE, INTERACTIVE}},
    {DROP_DOWN, {DRAWABLE, INTERACTIVE}},
    {OBJECT, {DRAWABLE, INTERACTIVE, ANIMATED}},
    {TRANTOR, {DRAWABLE, INTERACTIVE, ANIMATED, OBJECT}},
    {MATERIALS, {DRAWABLE, INTERACTIVE, ANIMATED, OBJECT}},
    {BACKGROUND, {DRAWABLE, INTERACTIVE, ANIMATED, OBJECT}}
};

} // visual
} // gui

#endif