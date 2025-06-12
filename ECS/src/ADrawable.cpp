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

void ADrawable::setRotation(float new_angle)
{
    _angle = new_angle;
}

float ADrawable::getRotation(void) const
{
    return _angle;
}

} // ecs
