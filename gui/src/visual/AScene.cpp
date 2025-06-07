/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.cpp
*/

#include "visual/AScene.hpp"

namespace gui {
namespace visual {

void AScene::display(void) const
{
    for (const ILayer& layer : _layers) {
        layer.display();
    }
}

void AScene::event(const sf::Event& event)
{
    for (ILayer& layer : _layers) {
        layer.event(event);
    }
}

} // visual
} // gui
