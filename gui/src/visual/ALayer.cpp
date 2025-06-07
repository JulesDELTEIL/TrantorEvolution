/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ALayer.cpp
*/

#include "visual/ALayer.hpp"

namespace gui {
namespace visual {

void ALayer::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<IDrawable>& drawable : _drawables) {
        target.draw(*drawable);
    }
}

void ALayer::event(const sf::Event& event)
{
    for (std::unique_ptr<IDrawable>& drawable : _drawables) {

    }
}

} // visual
} // gui
