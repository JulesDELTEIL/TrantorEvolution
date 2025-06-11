/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.cpp
*/

#include "visual/scenes/InGame.hpp"

#include "visual/layers/Land.hpp"

namespace gui {
namespace visual {

InGame::InGame() : AScene()
{
    _layers.emplace_back(std::make_unique<Land>());
}

void InGame::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ILayer>& layer : _layers)
        layer->display(target);
}

void InGame::event(const sf::Event& event)
{
    for (const std::unique_ptr<ILayer>& layer : _layers)
        layer->event(event);
}

} // visual
} // gui
