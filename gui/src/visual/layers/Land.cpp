/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include "visual/layers/Land.hpp"

#include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

Land::Land()
{
    loadMap({});
}

void Land::display(sf::RenderTarget& render) const
{
    for (const std::unique_ptr<IEntity>& entity : _entities)
        entity->display(render);
}

void Land::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
            for (const auto& entity : _entities)
                entity->updatePosition(sf::Vector2f(10, 0));
        }
        if (event.key.code == sf::Keyboard::D) {
            for (const auto& entity : _entities)
                entity->updatePosition(sf::Vector2f(-10, 0));
        }
        if (event.key.code == sf::Keyboard::Z) {
            for (const auto& entity : _entities)
                entity->updatePosition(sf::Vector2f(0, 10));
        }
        if (event.key.code == sf::Keyboard::S) {
            for (const auto& entity : _entities)
                entity->updatePosition(sf::Vector2f(0, -10));
        }
    }
}

void Land::loadMap(const std::vector<sf::Vector2f>&)
{
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(0, 0), GRASS));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(32, 0), GRASS));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(64, 0), SAND));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(16, 8), GRASS));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(48, 8), SAND));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(0, 16), SAND));
    _entities.emplace_back(std::make_unique<Tile>(sf::Vector2f(32, 16), SAND));
}

} // visual
} // gui
