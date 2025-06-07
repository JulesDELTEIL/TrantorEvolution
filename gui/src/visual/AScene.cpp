/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.cpp
*/

#include "visual/AScene.hpp"

namespace gui {
namespace visual {

void AScene::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ILayer>& layer : _layers) {
        layer->display(target);
    }
}

void AScene::event(const sf::Event& event)
{
    for (std::unique_ptr<ILayer>& layer : _layers) {
        layer->event(event);
    }
}

} // visual
} // gui
