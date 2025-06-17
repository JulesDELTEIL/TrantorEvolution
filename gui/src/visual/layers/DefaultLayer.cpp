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
    _entities.emplace_back(ecs::ECSFactory::createEntity("default", 0.0f, 0.0f));
}

void DefaultLayer::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ecs::IEntity>& entity : _entities) {
        entity->display(target);
    }
}

void DefaultLayer::event(const sf::Event& event, const NetPack&)
{
    for (std::unique_ptr<ecs::IEntity>& entity : _entities) {
        entity->event(event);
    }
}

} // visual
} // gui
