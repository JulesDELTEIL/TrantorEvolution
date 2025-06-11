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
    try {
        _entities.emplace_back(ecs::ECSFactory::create<ecs::IEntity>("tile", 0, 0, GRASS));
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
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
