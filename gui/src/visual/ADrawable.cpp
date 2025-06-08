/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ADrawable.cpp
*/

#include "visual/ADrawable.hpp"

namespace gui {
namespace visual {

ADrawable::ADrawable(sf::Vector2f entity_origin)
{
    this->setOrigin(entity_origin);
}

VisualType_e ADrawable::getId(void)
{
    return _type;
}

} // visual
} // gui
