/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.cpp
*/

#include "visual/entities/DefaultEntity.hpp"

namespace gui {
namespace visual {

DefaultEntity::DefaultEntity()
{

}

void DefaultEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables)
        win.draw(*drawable.second);
}

void DefaultEntity::event(const sf::Event&)
{
    
}

} // visual
} // gui
