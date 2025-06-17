/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.cpp
*/

#include "visual/scenes/InGame.hpp"
#include "core/Engine.hpp"

#include "visual/layers/Land.hpp"

namespace gui {
namespace visual {

InGame::InGame() : AScene(core::DEFAULT_VIEW)
{
    _layers.emplace_back(std::make_unique<Land>());
}

void InGame::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ILayer>& layer : _layers)
        layer->display(target);
}

void InGame::event(const sf::Event& event, const NetPack& net_events)
{
    for (const std::unique_ptr<ILayer>& layer : _layers)
        layer->event(event, net_events);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::D)
            move(10, 0);
        if (event.key.code == sf::Keyboard::Q)
            move(-10, 0);
        if (event.key.code == sf::Keyboard::S)
            move(0, 10);
        if (event.key.code == sf::Keyboard::Z)
            move(0, -10);
        if (event.key.code == sf::Keyboard::E)
            zoom(0.9);
        if (event.key.code == sf::Keyboard::A)
            zoom(1.1);
    }
}

} // visual
} // gui
