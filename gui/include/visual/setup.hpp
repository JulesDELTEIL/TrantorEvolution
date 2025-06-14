/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** setup.hpp
*/

#ifndef GUI_SETUP_HPP_
    #define GUI_SETUP_HPP_

    #include <memory>

    // DRAWABLES
    #include "visual/drawables/Biome.hpp"
    #include "visual/drawables/ResourceNode.hpp"

    // ENTITIES
    #include "visual/entities/Tile.hpp"

namespace gui {
namespace visual {

std::unique_ptr<ecs::IDrawable> makeBiome(float, float, int);
std::unique_ptr<ecs::IDrawable> makeResourceNode(float x, float y, int type);

std::unique_ptr<ecs::IEntity> makeTile(float x, float y, int type);

} // namespace visual
} // namespace gui


#endif
