/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Window.cpp
*/

#include "core/Window.hpp"

namespace gui {
namespace core {

Window::Window(void) : window(sf::VideoMode({WIN_X, WIN_Y}), "TrantorEvolution", sf::Style::Default, sf::ContextSettings(32))
{
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE_LIMIT);
    window.setActive(true);
}

} // core
} // gui