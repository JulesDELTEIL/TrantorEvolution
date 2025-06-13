/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultDrawable.cpp
*/

#include "DefaultEntity.hpp"

#include "PluginManager.hpp"
#include "ECSFactory.hpp"

namespace ecs {
    
DefaultEntity::DefaultEntity(float x, float y) : AEntity(sf::Vector2f(x, y))
{
    PluginManager::load();
    _drawables["default"] = ecs::ECSFactory::create<ecs::IDrawable>("default");
}

void DefaultEntity::display(sf::RenderTarget& win) const
{
    for (const auto& drawable : _drawables) {
        win.draw(*drawable.second);
    }
}

void DefaultEntity::event(const sf::Event&)
{

}

} // namespace ecs

