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

Tile::Tile(std::reference_wrapper<Drawable> biome, const sf::Vector2f& pos, biome_e type)
: _biome(biome), _tile_skin(std::rand() % TILE_SKIN_NB)
{
    _pos = pos;
    _type = type;
}

void Tile::draw(sf::RenderTarget& target, const sf::Clock& clock)
{
    sf::IntRect texture_rect = TEXTURE_RECT.at(_type);

    texture_rect.top += GET_ANIMATION(clock.getElapsedTime().asMilliseconds()) * ANIMATION_GAP;
    texture_rect.top += _tile_skin * SKIN_GAP;
    _biome.get().sprite.setTextureRect(texture_rect);
    _biome.get().sprite.setPosition(_pos);
    target.draw(_biome.get().sprite);
}

ResourceGroup Tile::getInventory(void) const
{
    return _resources;
}

void Tile::updateResource(resource_e type, int factor)
{
    _resources.at(type) += factor;
}


} // visual
} // gui
