/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.cpp
*/

#include "core/Core.hpp"

#include "visual/scenes/DefaultScene.hpp"
#include "visual/scenes/InGame.hpp"
#include "PluginManager.hpp"

namespace gui {
namespace core {

Core::Core()
{
    PluginManager::load("gui/plugins");
    _scenes[visual::Scene_e::NONE] = std::make_unique<visual::DefaultScene>();
    _scenes[visual::Scene_e::IN_GAME] = std::make_unique<visual::InGame>();
}

void Core::run(void)
{
    while (_engine.window.isOpen()) {
        events();
        display();
    }
}

void Core::display(void)
{
    _engine.window.clear();
    _scenes.at(_selected_scene)->display(_engine.window);
    _engine.window.display();
}

void Core::events(void)
{
    while (_engine.window.pollEvent(_engine.events)) {
        if (_engine.events.type == sf::Event::Closed)
            _engine.window.close();
        if (_engine.events.type == sf::Event::KeyPressed) {
            if (_engine.events.key.code == sf::Keyboard::G)
                _selected_scene = visual::Scene_e::IN_GAME;
        }
        _scenes.at(_selected_scene)->event(_engine.events);
    }
}

} // core
} // core
