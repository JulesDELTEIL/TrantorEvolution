/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include "visual/layers/Land.hpp"
#include "visual/visual.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

Land::Land(const std::vector<int>& map)
{
    loadMap(map);
}

void Land::display(sf::RenderTarget& render) const
{
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities)
        entity->display(render);
    for (const std::unique_ptr<Tile>& tile : _tiles)
        tile->display(render);
}

void Land::event(const sf::Event&)
{

}

void Land::loadMap(const std::vector<int>&)
{
    _tiles.emplace_back(dynamic_cast<Tile*>(
            ecs::ECSFactory::createEntity("tile", 0.0f, 0.0f, static_cast<int>(GRASS)).release()
    ));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 32.0f, 0.0f, static_cast<int>(GRASS)));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 64.0f, 0.0f, static_cast<int>(SAND)));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 16.0f, 8.0f, static_cast<int>(GRASS)));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 48.0f, 8.0f, static_cast<int>(SAND)));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 0.0f, 16.0f, static_cast<int>(SAND)));
    // _tiles.emplace_back(ecs::ECSFactory::createEntity("tile", 32.0f, 16.0f, static_cast<int>(SAND)));
}

} // visual
} // gui
