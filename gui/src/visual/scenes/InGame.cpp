/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** InGame.cpp
*/

#include "visual/scenes/InGame.hpp"
#include "core/Engine.hpp"

#include "visual/layers/Background.hpp"
#include "visual/layers/Land.hpp"

namespace gui {
namespace visual {

InGame::InGame() : AScene(core::DEFAULT_VIEW)
{
    _layers.emplace_back(std::make_unique<Background>());
    _layers.emplace_back(std::make_unique<Land>());
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
            move(MOVE_DELTA, 0);
        if (event.key.code == sf::Keyboard::Q)
            move(-MOVE_DELTA, 0);
        if (event.key.code == sf::Keyboard::S)
            move(0, MOVE_DELTA);
        if (event.key.code == sf::Keyboard::Z)
            move(0, -MOVE_DELTA);
        if (event.key.code == sf::Keyboard::E)
            zoom(1 - ZOOM_DELTA);
        if (event.key.code == sf::Keyboard::A)
            zoom(1 + ZOOM_DELTA);
    }
    switch (static_cast<int>(net_events.event)) {
    case network::TEAMS:
        writeTeams(net_events.pack[0].getString());
    }
}

void InGame::writeTeams(const std::string& name)
{
    _teams.push_back(name);
}

void InGame::zoom(float scale)
{
    sf::Vector2f size = _camera.getSize();

    if (size.x * scale > core::DEFAULT_VIEW.width || size.y * scale < 0.0f)
        return;
    _camera.zoom(scale);
}

void InGame::move(float x, float y)
{
    sf::Vector2f pos = _camera.getCenter();

    pos.x -= _camera.getSize().x / 2;
    pos.y -= _camera.getSize().y / 2;
    if (pos.x + x + _camera.getSize().x > core::DEFAULT_VIEW.width + VIEW_WIDTH / 2 ||
        pos.x + x < VIEW_WIDTH / 2)
        return;
    _camera.move(sf::Vector2f(x, y));
}

} // visual
} // gui
