/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.cpp
*/

#include <iostream>

#include "core/Core.hpp"

#include "visual/scenes/DefaultScene.hpp"
#include "visual/scenes/InGame.hpp"

#include "ECSFactory.hpp"
#include "visual/setup.hpp"

namespace gui {
namespace core {

Core::Core(int argc, const char *argv[])
{
    try {
        _parser = Parser(argc, argv);
        setupVisual();
        _scenes[visual::Scene_e::NONE] = std::make_unique<visual::DefaultScene>();
        changeScene(visual::Scene_e::NONE);
        _scenes[visual::Scene_e::IN_GAME] = std::make_unique<visual::InGame>();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(84);
    }
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
    _engine.window.setView(_scenes.at(_selected_scene)->getView());
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
                changeScene(visual::Scene_e::IN_GAME);
        }
        _scenes.at(_selected_scene)->event(_engine.events);
    }
}

void Core::changeScene(const visual::Scene_e& scene)
{
    _selected_scene = scene;
    _engine.window.setView(_scenes.at(_selected_scene)->getView());
}

void Core::setupVisual(void)
{
    ecs::ECSFactory::setDraw("biome", &visual::makeBiome);
    ecs::ECSFactory::setDraw("resource_node", &visual::makeResourceNode);
    ecs::ECSFactory::setEntity("tile", &visual::makeTile);
}

} // core
} // core
