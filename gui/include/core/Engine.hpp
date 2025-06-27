/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Engine.hpp
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include "audio/SoundManage.hpp"

    #include <SFML/Graphics.hpp>

namespace gui {
namespace core {

    #define WIN_X 1280
    #define WIN_Y 720

    #define FRAMERATE_LIMIT 60

    #define VIEW_WIDTH 1920.0f
    #define VIEW_HEIGHT 1080.0f

static const sf::FloatRect DEFAULT_VIEW = {VIEW_WIDTH / 2, VIEW_HEIGHT / 2, VIEW_WIDTH, VIEW_HEIGHT};

struct Engine {
    Engine();
    sf::RenderWindow window;
    sf::Event events;
    sf::Clock runTime;
    SoundManage trantorSound;
};

} // core
} // gui

#endif
