/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.cpp
*/

#include <cstdlib>

#include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

Tile::Tile(std::reference_wrapper<Drawable> biome, const sf::Vector2f& pos, biome_e type) : _biome(biome)
{
    _pos = pos;
    _type = type;
}

void Tile::draw(sf::RenderTarget& target, const sf::Clock& clock)
{
    _biome.get().sprite.setTextureRect(TEXTURE_RECT.at(_type));
    _biome.get().sprite.setPosition(_pos);
    target.draw(_biome.get().sprite);
}

} // visual
} // gui
