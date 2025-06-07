/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.cpp
*/

#include "core/Core.hpp"

namespace gui {
namespace core {

Core::Core()
: _selected_scene(visual::Scene_e::MENU)
{

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
    _scenes.at(_selected_scene)->display();
    _engine.window.display();
}

void Core::events(void)
{
    while (_engine.window.pollEvent(_engine.events)) {
        if (_engine.events.type == sf::Event::Closed)
            _engine.window.close();
        _scenes.at(_selected_scene)->event(_engine.events);
    }
}

} // core
} // core
