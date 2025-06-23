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

Tile::Tile(const sf::Vector2f& pos, biome_e type)
{
    int random = std::rand() % NB_TYPE;
    sf::IntRect rect = TEXTURE_RECT.at(type);

    rect.top += 32 * random;
    _biome.texture.loadFromFile(BIOME_TEXTURE_PATH);
    _biome.sprite.setTexture(_biome.texture);
    _biome.sprite.setTextureRect(rect);
    _biome.sprite.setPosition(pos);
    _biome.sprite.setOrigin({16.0f, 0.0f});
}

void Tile::draw(sf::RenderTarget& target)
{
    target.draw(_biome.sprite);
}

} // visual
} // gui
