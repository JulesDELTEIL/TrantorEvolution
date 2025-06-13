/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.cpp
*/

#include "default/DefaultDrawable.hpp"

namespace ecs {
    
DefaultDrawable::DefaultDrawable(float x, float y) :
    AObject(sf::Vector2f(x, y), DEFAULT_TEXTURE, DEFAULT_TEXTURE_RECT)
{

}
    
} // namespace ecs
