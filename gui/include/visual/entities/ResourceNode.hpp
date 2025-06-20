/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.hpp
*/

#ifndef RESOURCE_NODE_HPP_
    #define RESOURCE_NODE_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>

    #include "visual/visual.hpp"
    #include "visual/Drawable.hpp"

    #define RES_MAX_X 8
    #define RES_MIN_X -8
    #define RES_MAX_Y 13
    #define RES_MIN_Y 3

static const int RES_RANGE_X = RES_MAX_X - RES_MIN_X + 1;
static const int RES_RANGE_Y = RES_MAX_Y - RES_MIN_Y + 1;

    #define MIN_SCALE 0.15f
    #define SCALE_RATIO 100

namespace gui {
namespace visual {

static const std::map<ResourceType_e, std::string> RESOURCE_NODE_TEXTURE  = {
    {WOOD, "assets/ressources/Grass_Biom_Tree.png"},
    {STONE, "assets/ressources/Stone.png"},
    {CLAY, "assets/ressources/Clay.png"},
    {METAL, "assets/ressources/Metal.png"},
    {OIL, "assets/ressources/Grass_Biom_Tree.png"},
    {ANTI_MATTER, "assets/ressources/Grass_Biom_Tree.png"}
};

static const sf::IntRect RESOURCE_RECT(0, 0, 30, 30);

class ResourceNode {
    public:
        ResourceNode(const sf::Vector2f& pos, ResourceType_e type, size_t quantity);
        ~ResourceNode() = default;

        void draw(sf::RenderTarget&);
        sf::Vector2f getCollectPosition(void);
        void addQuantity(size_t);
        ResourceType_e getType(void);

    private:
        Drawable _resource;

        ResourceType_e _type;
        size_t _quantity;

};

} // visual
} // gui

#endif
