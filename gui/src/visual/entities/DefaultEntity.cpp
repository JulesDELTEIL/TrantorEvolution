/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultEntity.cpp
*/

#include "visual/entities/DefaultEntity.hpp"
#include "visual/drawables/Tree.hpp"
#include "visual/drawables/ResourceNode.hpp"

namespace gui {
namespace visual {

DefaultEntity::DefaultEntity()
{
    _drawables["tree_sprite"] = std::make_unique<Tree>(sf::Vector2f(100, 100));
    _drawables["tree_sprite2"] = std::make_unique<Tree>(sf::Vector2f(200, 100));
    _drawables["wood_node1"] = std::make_unique<ResourceNode>(sf::Vector2f(400, 100), WOOD);
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
            _drawables.at("tree_sprite")->setPosition(
                sf::Vector2f(
                    _drawables.at("tree_sprite")->getPosition().x + 30,
                    _drawables.at("tree_sprite")->getPosition().y
                )
            );
        if (event.key.code == sf::Keyboard::Q)
            _drawables.at("tree_sprite")->setPosition(
                sf::Vector2f(
                    _drawables.at("tree_sprite")->getPosition().x - 30,
                    _drawables.at("tree_sprite")->getPosition().y
                )
            );
    }
}

} // visual
} // gui
