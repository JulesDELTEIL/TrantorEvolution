/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Engine.hpp
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <SFML/Graphics.hpp>

namespace gui {
namespace core {

    #define WIN_X 1280
    #define WIN_Y 720

    #define FRAMERATE_LIMIT 60

static const sf::FloatRect DEFAULT_VIEW = {0, 0, WIN_X, WIN_Y};

struct Engine {
    Engine();
    sf::RenderWindow window;
    sf::Event events;
    sf::Clock runTime;
};

} // core
} // gui

#endif
