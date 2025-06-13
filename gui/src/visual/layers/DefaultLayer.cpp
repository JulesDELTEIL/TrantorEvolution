/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultLayer.cpp
*/

#include "visual/layers/DefaultLayer.hpp"
#include "visual/visual.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

DefaultLayer::DefaultLayer()
{
    _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("caca qui peu"));
}

void DefaultLayer::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities) {
        entity->display(target);
    }
}

void DefaultLayer::event(const sf::Event& event)
{
    for (std::unique_ptr<ecs::IEntity>& entity : _entities) {
        entity->event(event);
    }
}

} // visual
} // gui
