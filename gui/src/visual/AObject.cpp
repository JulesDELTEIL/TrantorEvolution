/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AObject.cpp
*/

#include "visual/AObject.hpp"

namespace gui {
namespace visual {

AObject::AObject(const sf::Vector2f& entity_origin) :
    ADrawable(entity_origin), sf::Sprite()
{
    _type = ANIMATED;
    this->setPosition(entity_origin);
}

} // visual
} // gui
