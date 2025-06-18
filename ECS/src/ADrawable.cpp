/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ADrawable.cpp
*/

#include "interfaces/ADrawable.hpp"

namespace ecs {

ADrawable::ADrawable(sf::Vector2f entity_pos)
{
    _pos = entity_pos;
}

void ADrawable::setPosition(const sf::Vector2f& new_pos)
{
    _pos = new_pos;
}

sf::Vector2f ADrawable::getPosition(void) const
{
    return _pos;
}

void ADrawable::setScale(const sf::Vector2f& new_scale)
{
    _scale = new_scale;
}

sf::Vector2f ADrawable::getScale(void) const
{
    return _scale;
}

void ADrawable::changeState(int state)
{
    _state = state;
}

int ADrawable::getState(void)
{
    return _state;
}

} // ecs
