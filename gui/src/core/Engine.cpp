/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Engine.cpp
*/

#include "core/Engine.hpp"

namespace gui {
namespace core {

Engine::Engine(void) : window(sf::VideoMode({WIN_X, WIN_Y}), "TrantorEvolution", sf::Style::Default, sf::ContextSettings(24))
{
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE_LIMIT);
    window.setActive(true);
}

} // core
} // gui