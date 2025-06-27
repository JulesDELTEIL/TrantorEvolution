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
    #include "visual/Animation.hpp"

namespace gui {
namespace visual {

    #define BACKGROUND_PATH "assets/background.png"
    #define WATERFALL_PATH "assets/tiles/waterfall.png"
    #define WATERFALL_ANIM {"assets/tiles/waterfall.png", {96, 200}, {3, 1}, {0, 0}, 0.4, sf::Clock()}

    #define TILE_SIZE 96

    #define CENTER_MAP(map_height) (sf::Vector2f(VIEW_WIDTH, (VIEW_HEIGHT * 2 - map_height * TILE_SIZE) / 2))
    #define MAP_POS(middle, tx, ty) (sf::Vector2f((middle.x - (TILE_SIZE / 2) * (tx + ty)) + (TILE_SIZE * ty), middle.y + (24 * (tx + ty))))

class Background {
    public:
        Background();
        ~Background() = default;
    
        void drawBackground(sf::RenderTarget& render);
        void drawWaterfall(sf::RenderTarget& render, const sf::Vector2f& map_size);

    private:
        Drawable _background;
        Drawable _waterfall;
        Animation _waterfall_anim;

};
    
} // namespace visual
} // namespace gui

#endif
