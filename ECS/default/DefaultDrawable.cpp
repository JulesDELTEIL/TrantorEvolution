/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.cpp
*/

#include "DefaultDrawable.hpp"

namespace ecs {
    
DefaultDrawable::DefaultDrawable(float x, float y) :
    AObject(sf::Vector2f(x, y), DEFAULT_TEXTURE, sf::IntRect(0, 0, 800, 800))
{

}
    
} // namespace ecs
