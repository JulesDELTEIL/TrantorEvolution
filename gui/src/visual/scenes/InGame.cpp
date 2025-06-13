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

InGame::InGame() : AScene(sf::FloatRect(0, 0, 600, 338))
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
