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
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    setupVisual();
    _scenes[visual::Scene_e::NONE] = std::make_unique<visual::DefaultScene>();
    _scenes[visual::Scene_e::IN_GAME] = std::make_unique<visual::InGame>();
    changeScene(visual::Scene_e::IN_GAME);
    try {
        _client.setSocket(_parser.getHostName(), _parser.getPortNb());
    } catch (const network::Socket::socketError& e) {
        std::cerr << e.what() << std::endl;
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
    NetPack net_event;

    while (_engine.window.pollEvent(_engine.events) || _client.pollEvent(net_event)) {
        if (_engine.events.type == sf::Event::Closed)
            _engine.window.close();
        _scenes.at(_selected_scene)->event(_engine.events, net_event);
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
    ecs::ECSFactory::setDraw("body", &visual::makeBody);
    ecs::ECSFactory::setEntity("tile", &visual::makeTile);
    ecs::ECSFactory::setEntity("trantorian", &visual::makeTrantorian);
}

} // core
} // core
