/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ressource.hpp
*/

#ifndef RESOURCENODE_HPP_
    #define RESOURCENODE_HPP_

    #include "visual/AAnimated.hpp" 

namespace gui {
namespace visual {

class ResourceNode : public AAnimated {
    public:
        ResourceNode(const sf::Vector2f& pos, ResourceType_e type);
        ~ResourceNode() = default;

        void animation(void) {};
};

static const std::map<ResourceType_e, std::string> RESOURCE_NODE_TEXTURE  = {
    {WOOD, "assets/ressources/Grass_Biom_Tree.png"},
    {STONE, "assets/ressources/Grass_Biom_Tree.png"},
    {CLAY, "assets/ressources/Grass_Biom_Tree.png"},
    {METAL, "assets/ressources/Grass_Biom_Tree.png"},
    {OIL, "assets/ressources/Grass_Biom_Tree.png"},
    {ANTI_MATTER, "assets/ressources/Grass_Biom_Tree.png"}
};

} // gui
} // visual

#endif