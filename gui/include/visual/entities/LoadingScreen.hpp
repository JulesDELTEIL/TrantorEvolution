/*
** EPITECH PROJECT, 2024
** TrantorEvolution
** File description:
** LoadingScreen.hpp
*/

#ifndef LOADING_SCREEN_HPP_
    #define LOADING_SCREEN_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <SFML/Graphics/RectangleShape.hpp>

    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

    #define LOAD_BAR_PATH "assets/loading/load_bar.png"
    #define LOAD_BAR_SCALE 4.0f
    #define LOAD_BG_PATH "assets/loading/bg.png"

class LoadingScreen {
    public:
        LoadingScreen(const sf::FloatRect&);
        ~LoadingScreen() = default;

        void draw(sf::RenderTarget&);
        void loadingPercent(float);

    private:
        Drawable _bar;
        sf::RectangleShape _load_done;
        Drawable _background;
        sf::Vector2f _bar_size;
};

} // namespace visual
} // namespace gui


#endif