/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AMenu.cpp
*/

#include "visual/AMenu.hpp"

namespace gui {
namespace visual {

void AMenu::display(void) const
{
    for (const ILayer& layer : _layers) {
        layer.display();
    }
}

void AMenu::event(const sf::Event& event)
{
    for (ILayer& layer : _layers) {
        layer.event(event);
    }
}

} // visual
} // gui
