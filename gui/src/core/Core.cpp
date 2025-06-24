/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.cpp
*/

#include <iostream>

#include "core/Core.hpp"
#include "visual/scenes/InGame.hpp"

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
    network::NetEventPack net_event;
    sf::Event default_event;

    while (_engine.window.pollEvent(_engine.events)) {
        if (_engine.events.type == sf::Event::Closed)
            _engine.window.close();
        _scenes.at(_selected_scene)->event(_engine.events, net_event);
    }
    default_event.type = sf::Event::SensorChanged;
    while (_client.pollEvent(net_event)) {
        if (net_event.event == network::CON) {
            _client.sendData("GRAPHIC\n");
            _client.sendData("msz\n");
            _client.sendData("mct\n");
            _client.sendData("sgt\n");
        }
        _scenes.at(_selected_scene)->event(default_event, net_event);
    }
}

void Core::changeScene(const visual::Scene_e& scene)
{
    _selected_scene = scene;
    _engine.window.setView(_scenes.at(_selected_scene)->getView());
}

} // core
} // core
