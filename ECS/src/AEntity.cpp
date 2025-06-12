/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AEntity.cpp
*/

#include <iostream> // test purpose (to delet)
#include "interfaces/AEntity.hpp"

namespace ecs {

AEntity::AEntity(const sf::Vector2f& pos)
{
    _origin = pos;
}

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
        drawable.second->setPosition(new_pos);
}

void AEntity::updatePosition(const sf::Vector2f& factor)
{
    for (const auto& drawable : _drawables)
        drawable.second->setPosition(drawable.second->getPosition() + factor);
}

void AEntity::setRotation(float new_angle)
{
    for (const auto& drawable : _drawables)
        drawable.second->setRotation(new_angle);
}

void AEntity::updateRotation(float factor)
{
    for (const auto& drawable : _drawables)
        drawable.second->setRotation(drawable.second->getRotation() + factor);
}

} // ecs
