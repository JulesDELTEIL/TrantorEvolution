/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Background.hpp
*/

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_

    #include <SFML/Window/Event.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "network/events.hpp"
    #include "core/Engine.hpp"
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

    #define BACKGROUND_PATH "assets/background.png"
    #define WATERFALL_PATH "assets/tiles/waterfall.png"
    #define WATERFALL_RECT sf::IntRect(0, 0, 96, 200)

    #define TILE_SIZE 96

    #define CENTER_MAP(map_height) (sf::Vector2f(VIEW_WIDTH, (VIEW_HEIGHT * 2 - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, x, y) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (x + y)) + (TILE_SIZE * y), middle.y + (24 * (x + y))))

class Background {
    public:
        Background();
        ~Background() = default;
    
        void drawBackground(sf::RenderTarget& render);
        void drawWaterfall(sf::RenderTarget& render, const sf::Vector2f& map_size);

    private:
        Drawable _background;
        Drawable _waterfall;

};
    
} // namespace visual
} // namespace gui

#endif
