/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Biome.hpp
*/

#ifndef BIOME_HPP_
    #define BIOME_HPP_

    #include <memory>
    #include <SFML/Graphics/Rect.hpp>

    #include "visual/visual.hpp"
    #include "interfaces/AObject.hpp"

namespace gui {
namespace visual {

    #define BIOME_TEXTURE_PATH "assets/tiles/BiomTiles.png"

static const std::map<BiomeTypes_e, sf::IntRect> TEXTURE_RECT = {
    {GRASS, sf::IntRect(0, 0, 32, 32)},
    {SAND, sf::IntRect(32, 0, 32, 32)},
    {SEA, sf::IntRect(64, 0, 32, 32)},
};

class Biome : public ecs::AObject{
    public:
        Biome(const sf::Vector2f&, BiomeTypes_e);
        ~Biome() = default;

    private:

};

} // visual
} // gui

#endif
