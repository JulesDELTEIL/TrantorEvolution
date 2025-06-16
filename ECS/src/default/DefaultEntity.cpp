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
    _drawables[DEFAULT_ID] = ECSFactory::createDraw(DEFAULT_ID, x, y);
}

void DefaultEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        drawable.second->draw(win);
    }
}

void DefaultEntity::event(const sf::Event&)
{

}

} // namespace ecs

