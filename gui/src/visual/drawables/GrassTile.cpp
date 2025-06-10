/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** GrassTile.cpp
*/

#include "visual/drawables/GrassTile.hpp"

namespace gui {
namespace visual {

GrassTile::GrassTile(const sf::Vector2f& pos) : AObject(pos)
{
    _texture.loadFromFile(GRASS_TILE_TEXTURE);
}

} // visual
} // gui
