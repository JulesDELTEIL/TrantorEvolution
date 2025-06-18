/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <memory>
    #include <SFML/Graphics/Rect.hpp>
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "visual/visual.hpp"
    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

   #define BIOME_TEXTURE_PATH "assets/tiles/BiomTiles.png"

static const std::map<BiomeTypes_e, sf::IntRect> TEXTURE_RECT = {
    {GRASS, sf::IntRect(0, 0, 32, 32)},
    {SAND, sf::IntRect(32, 0, 32, 32)},
    {SEA, sf::IntRect(64, 0, 32, 32)},
};

class Tile {
    public:
        Tile(const sf::Vector2f& pos, BiomeTypes_e type);
        ~Tile() = default;

        void draw(sf::RenderTarget&);

    private:
        Drawable _biome;

};

} // visual
} // gui

#endif
