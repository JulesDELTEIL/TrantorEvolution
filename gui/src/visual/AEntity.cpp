/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AEntity.cpp
*/

#include "visual/AEntity.hpp"

namespace gui {
namespace visual {

void AEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables)
        win.draw(*drawable.second);
}

void AEntity::event(const sf::Event&)
{

}

void AEntity::setPosition(const sf::Vector2f& new_pos)
{
    for (const auto& drawable : _drawables)
        drawable.second->setDrawPosition(new_pos);
}

void AEntity::updatePosition(const sf::Vector2f& factor)
{
    for (const auto& drawable : _drawables)
        drawable.second->setDrawPosition(drawable.second->getDrawPosition() + factor);
}

void AEntity::setRotation(float new_angle)
{
    for (const auto& drawable : _drawables)
        drawable.second->setDrawRotation(new_angle);
}

void AEntity::updateRotation(float factor)
{
    for (const auto& drawable : _drawables)
        drawable.second->setDrawRotation(drawable.second->getDrawRotation() + factor);
}


} // visual
} // gui
