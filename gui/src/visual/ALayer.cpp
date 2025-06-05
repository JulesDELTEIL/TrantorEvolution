/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ALayer.cpp
*/

#include "visual/ALayer.hpp"

namespace gui {
namespace visual {

void ALayer::display(void) const
{
    for (const std::unique_ptr<int>& draw : _drawables) {

    }
}

void ALayer::event(const sf::Event& event)
{
    for (const std::unique_ptr<int>& draw : _drawables) {

    }
}

} // visual
} // gui
