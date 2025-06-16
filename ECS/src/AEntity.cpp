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
        drawable.second->draw(win);
}

void AEntity::event(const sf::Event&)
{

}

void AEntity::updatePosition(const sf::Vector2f& factor)
{
    for (const auto& drawable : _drawables)
        drawable.second->setPosition(drawable.second->getPosition() + factor);
}

} // ecs
