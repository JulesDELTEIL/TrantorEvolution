/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.cpp
*/

#include "visual/entities/DefaultEntity.hpp"
#include "visual/drawables/ResourceNode.hpp"

namespace gui {
namespace visual {

DefaultEntity::DefaultEntity()
{
    _drawables["wood_node1"] = std::make_unique<ResourceNode>(sf::Vector2f(100, 100), WOOD);
    _drawables["stone_node1"] = std::make_unique<ResourceNode>(sf::Vector2f(100, 200), STONE);
    _drawables["clay_node1"] = std::make_unique<ResourceNode>(sf::Vector2f(100, 300), CLAY);
    _drawables["metal_node1"] = std::make_unique<ResourceNode>(sf::Vector2f(100, 400), METAL);
}

void DefaultEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        win.draw(*drawable.second);
    }
}

void DefaultEntity::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::E)
            updatePosition(sf::Vector2f(10, 0));
        if (event.key.code == sf::Keyboard::A)
            updatePosition(sf::Vector2f(-10, 0));
        if (event.key.code == sf::Keyboard::D)
            _drawables.at("wood_node1")->setPosition(
                sf::Vector2f(
                    _drawables.at("wood_node1")->getPosition().x + 30,
                    _drawables.at("wood_node1")->getPosition().y
                )
            );
        if (event.key.code == sf::Keyboard::Q)
            _drawables.at("wood_node1")->setPosition(
                sf::Vector2f(
                    _drawables.at("wood_node1")->getPosition().x - 30,
                    _drawables.at("wood_node1")->getPosition().y
                )
            );
    }
}

} // visual
} // gui
