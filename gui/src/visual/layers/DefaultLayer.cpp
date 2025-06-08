/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultLayer.cpp
*/

#include "visual/layers/DefaultLayer.hpp"

namespace gui {
namespace visual {

DefaultLayer::DefaultLayer()
{
    
}

void DefaultLayer::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<IEntity>& entity : _entities) {
        entity->display(target);
    }
}

void DefaultLayer::event(const sf::Event& event)
{
    for (std::unique_ptr<IEntity>& entity : _entities) {
        entity->event(event);
    }
}

} // visual
} // gui
