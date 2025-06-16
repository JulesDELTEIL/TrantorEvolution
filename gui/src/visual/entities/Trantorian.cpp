/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.cpp
*/

#include <iostream> // test purspose (to delete)

#include "visual/entities/Trantorian.hpp"
#include "ECSFactory.hpp"

namespace gui {
namespace visual {

Trantorian::Trantorian(const sf::Vector2f& pos) : AEntity(pos)
{
    _drawables["body"] = ecs::ECSFactory::createDraw("body", pos.x, pos.y);
}

void Trantorian::display(sf::RenderTarget& render) const
{
    for (const auto& drawable : _drawables)
        drawable.second->draw(render);
}

void Trantorian::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        return;
}

} // visual
} // gui
