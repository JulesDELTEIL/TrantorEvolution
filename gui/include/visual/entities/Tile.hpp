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

   #define BIOME_TEXTURE_PATH "assets/tiles/BiomTiles.png"
   #define NB_TYPE 3

static const std::map<biome_e, sf::IntRect> TEXTURE_RECT = {
    {PLAINS, sf::IntRect(0, 0, 96, 96)},
    {BEACH, sf::IntRect(96, 0, 96, 96)},
    {SEA, sf::IntRect(192, 0, 96, 96)},
    {MOUNTAINS, sf::IntRect(288, 0, 96, 96)},
    {FOREST, sf::IntRect(384, 0, 96, 96)},
    {EMPTY, sf::IntRect(480, 0, 96, 96)}
};

class Tile {
    public:
        Tile(const sf::Vector2f& pos, biome_e type);
        ~Tile() = default;

        void draw(sf::RenderTarget&, const sf::Clock&);

    private:
        Drawable _biome;

};

} // visual
} // gui

#endif
