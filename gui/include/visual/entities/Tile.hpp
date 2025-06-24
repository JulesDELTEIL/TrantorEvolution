/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <memory>
    #include <map>
    #include <SFML/System/Clock.hpp>
    #include <SFML/Graphics/Rect.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "map_tools.h"
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

    #define TILE_SIZE 96
    #define BIOME_TEXTURE_PATH "assets/tiles/BiomTiles.png"
    #define NB_TYPE 3
    #define ANIMATION_CLOCK 500
    #define ANIMATION_GAP 288
    #define SKIN_GAP 96
    #define TILE_SKIN_NB 3
    #define GET_ANIMATION(clock) (clock / ANIMATION_CLOCK % 2)

static const std::map<biome_e, sf::IntRect> TEXTURE_RECT = {
    {PLAINS, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE)},
    {BEACH, sf::IntRect(96, 0, TILE_SIZE, TILE_SIZE)},
    {SEA, sf::IntRect(192, 0, TILE_SIZE, TILE_SIZE)},
    {MOUNTAINS, sf::IntRect(288, 0, TILE_SIZE, TILE_SIZE)},
    {FOREST, sf::IntRect(384, 0, TILE_SIZE, TILE_SIZE)},
    {EMPTY, sf::IntRect(480, 0, TILE_SIZE, TILE_SIZE)}
};

class Tile {
    public:
        Tile(std::reference_wrapper<Drawable> biome, const sf::Vector2f& pos, biome_e type);
        ~Tile() = default;

        void draw(sf::RenderTarget&, const sf::Clock&);

    private:
        std::reference_wrapper<Drawable> _biome;
        uint8_t _tile_skin;
        sf::Vector2f _pos;
        biome_e _type;

};

} // visual
} // gui

#endif
