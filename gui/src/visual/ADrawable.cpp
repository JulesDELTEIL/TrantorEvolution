/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ADrawable.cpp
*/

#include "visual/ADrawable.hpp"

namespace gui {
namespace visual {

ADrawable::ADrawable(sf::Vector2f entity_pos)
{
    _pos = entity_pos;
}

VisualType_e ADrawable::getId(void)
{
    return _type;
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

} // visual
} // gui
