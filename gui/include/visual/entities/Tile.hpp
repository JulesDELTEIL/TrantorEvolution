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
    #include <SFML/Graphics/Rect.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "map_tools.h"
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

   #define BIOME_TEXTURE_PATH "assets/tiles/BiomTiles.png"
   #define NB_TYPE 3

static const std::map<biome_e, sf::IntRect> TEXTURE_RECT = {
    {SEA, sf::IntRect(64, 0, 32, 32)},
    {FOREST, sf::IntRect(128, 0, 32, 32)},
    {MOUNTAINS, sf::IntRect(96, 0, 32, 32)},
    {PLAINS, sf::IntRect(0, 0, 32, 32)},
    {BEACH, sf::IntRect(32, 0, 32, 32)},
    {EMPTY, sf::IntRect(160, 0, 32, 32)}
};

class Tile {
    public:
        Tile(std::reference_wrapper<Drawable> biome, const sf::Vector2f& pos, biome_e type);
        ~Tile() = default;

        void draw(sf::RenderTarget&);

    private:
        std::reference_wrapper<Drawable> _biome;
        sf::Vector2f _pos;
        biome_e _type;

};

} // visual
} // gui

#endif
