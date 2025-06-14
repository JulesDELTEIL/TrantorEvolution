/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultDrawable.cpp
*/

#include "default/DefaultEntity.hpp"
#include "ECSFactory.hpp"

namespace ecs {

DefaultEntity::DefaultEntity(float x, float y, ...) : AEntity(sf::Vector2f(x, y))
{
    _drawables["default"] = ECSFactory::createDraw("default", x, x);
}

void DefaultEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        win.draw(*drawable.second);
    }
}

void DefaultEntity::event(const sf::Event&)
{

}

} // namespace ecs

