/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.cpp
*/

#include "visual/scenes/InGame.hpp"
#include "core/Engine.hpp"

#include "visual/layers/Land.hpp"
#include "visual/layers/Hud.hpp"

namespace gui {
namespace visual {

InGame::InGame(std::reference_wrapper<network::Client> client) : AScene(core::DEFAULT_VIEW)
{
    _layers.emplace_back(std::make_unique<Land>(client));
    _layers.emplace_back(std::make_unique<Hud>());
}

void InGame::display(sf::RenderTarget& target)
{
    for (const std::unique_ptr<ILayer>& layer : _layers)
        layer->display(target);
}

void InGame::event(const sf::Event& event, const network::NetEventPack& net_events)
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
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
            checkHudHit(sf::Mouse::getPosition());
    }
}

void InGame::checkHudHit(const sf::Vector2i&)
{

}

} // visual
} // gui
