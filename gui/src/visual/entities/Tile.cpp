/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.cpp
*/

#include "visual/entities/Tile.hpp"

#include "visual/drawables/Biome.hpp"
#include "visual/drawables/Tree.hpp"

namespace gui {
namespace visual {

Tile::Tile(const sf::Vector2f& pos, BiomeTypes_e type) : AEntity(pos)
{
    _drawables["background"] = std::make_unique<Biome>(pos, type);
    if (type == GRASS)
        _drawables["tree"] = std::make_unique<Tree>(sf::Vector2f(pos.x + 8, pos.y + 8));
}

void Tile::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        win.draw(*drawable.second);
    }
}

void Tile::event(const sf::Event&)
{

}


} // visual
} // gui
