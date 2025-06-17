/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ResourceNode.hpp
*/

#ifndef RESOURCE_NODE_HPP_
    #define RESOURCE_NODE_HPP_

    #include "visual/visual.hpp"
    #include "interfaces/AEntity.hpp"

    #define RES_MAX_X 25
    #define RES_MIN_X 8
    #define RES_MAX_Y 9
    #define RES_MIN_Y 4

static const int RES_RANGE_X = RES_MAX_X - RES_MIN_X + 1;
static const int RES_RANGE_Y = RES_MAX_Y - RES_MIN_Y + 1;

namespace gui {
namespace visual {

class ResourceNode : public ecs::AEntity {
    public:
        ResourceNode(const sf::Vector2f& pos, ResourceType_e type);
        ~ResourceNode() = default;

        void display(sf::RenderTarget& render) const override;
        void event(const sf::Event& event) override;

    private:

};

} // visual
} // gui

#endif
