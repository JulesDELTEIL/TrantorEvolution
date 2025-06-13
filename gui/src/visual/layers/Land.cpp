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

Land::Land()
{
    loadMap({});
}

void Land::display(sf::RenderTarget& render) const
{
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities)
        entity->display(render);
}

void Land::event(const sf::Event& event)
{

}

void Land::loadMap(const std::vector<sf::Vector2f>&)
{
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 0.0f, 0.0f, static_cast<int>(GRASS)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 32.0f, 0.0f, static_cast<int>(GRASS)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 64.0f, 0.0f, static_cast<int>(SAND)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 16.0f, 8.0f, static_cast<int>(GRASS)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 48.0f, 8.0f, static_cast<int>(SAND)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 0.0f, 16.0f, static_cast<int>(SAND)));
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 32.0f, 16.0f, static_cast<int>(SAND)));
}

} // visual
} // gui
