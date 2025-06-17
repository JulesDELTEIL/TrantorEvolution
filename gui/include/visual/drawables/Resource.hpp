/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Resource.hpp
*/

#ifndef RESOURCE_HPP_
    #define RESOURCE_HPP_

    #include <memory>

    #include "visual/visual.hpp"
    #include "interfaces/AObject.hpp" 

namespace gui {
namespace visual {

class Resource : public ecs::AObject {
    public:
        Resource(const sf::Vector2f& pos, ResourceType_e type);
        ~Resource() = default;
};

static const std::map<ResourceType_e, std::string> RESOURCE_NODE_TEXTURE  = {
    {WOOD, "assets/ressources/Grass_Biom_Tree.png"},
    {STONE, "assets/ressources/Stone.png"},
    {CLAY, "assets/ressources/Clay.png"},
    {METAL, "assets/ressources/Metal.png"},
    {OIL, "assets/ressources/Grass_Biom_Tree.png"},
    {ANTI_MATTER, "assets/ressources/Grass_Biom_Tree.png"}
};

static const sf::IntRect RESOURCE_RECT(0, 0, 30, 30);

} // gui
} // visual


#endif