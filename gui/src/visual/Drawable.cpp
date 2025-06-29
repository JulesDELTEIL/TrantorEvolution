/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Drawable.cpp
*/

#include "visual/Drawable.hpp"

namespace gui {
namespace visual {

Drawable::Drawable(const std::string& path, float scale)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
}

} // visual
} // gui
