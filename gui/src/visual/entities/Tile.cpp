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

Tile::Tile(const sf::Vector2f& pos, BiomeTypes_e type)
{
    _biome.texture.loadFromFile(BIOME_TEXTURE_PATH);
    _biome.sprite.setTexture(_biome.texture);
    _biome.sprite.setTextureRect(TEXTURE_RECT.at(type));
    _biome.sprite.setPosition(pos);
}

void Tile::draw(sf::RenderTarget& target)
{
    target.draw(_biome.sprite);
}

} // visual
} // gui
