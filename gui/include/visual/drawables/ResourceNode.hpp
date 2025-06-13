/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ressource.hpp
*/

#ifndef RESOURCENODE_HPP_
    #define RESOURCENODE_HPP_

    #include <memory>

    #include "visual/visual.hpp"
    #include "interfaces/AAnimated.hpp" 

namespace gui {
namespace visual {

class ResourceNode : public ecs::AAnimated {
    public:
        ResourceNode(const sf::Vector2f& pos, ResourceType_e type);
        ~ResourceNode() = default;

        void animation(void) {};
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

std::unique_ptr<ecs::IDrawable> resource_nodeEntrypoint(float x, float y, int type) {
    return std::make_unique<ResourceNode>(sf::Vector2f(x, y), ResourceType_e(type));
}

} // gui
} // visual


#endif