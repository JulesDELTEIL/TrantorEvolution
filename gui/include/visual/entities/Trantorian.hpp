/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.hpp
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>
    #include <memory>

    #include "visual/entities/ResourceNode.hpp"

    #include "visual/Drawable.hpp"
    #include "visual/Animation.hpp"
    #include "visual/Movement.hpp"

namespace gui {
namespace visual {

enum BodyAnimIndex {
    IDLE = 0,
    WALK,
    COLLECT,
};

    #define NB_BODY_ANIM 3

static const std::vector<AnimationInfos> BODY_ANIM_INFOS = {
    {"assets/trantorians/body/Idle_Side-Sheet.png", {64, 64}, {4, 1}, {0, 0}, 0.3, sf::Clock()},
    {"assets/trantorians/body/Walk_Side-Sheet.png", {64, 64}, {6, 1}, {0, 0}, 0.1, sf::Clock()},
    {"assets/trantorians/body/Collect_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()}
};

class Trantorian {
    public:
        Trantorian(const sf::Vector2f& pos, const sf::Vector2i& pos_in_map, size_t level);
        ~Trantorian() = default;

        void draw(sf::RenderTarget&);
        void collect(const std::vector<std::shared_ptr<ResourceNode>>&, float);
        void move(const sf::Vector2f&, float);

        sf::Vector2i map_pos;
    private:
        BodyAnimIndex _type;
        size_t _lvl;
        Drawable _body;
        Animation _body_animation;
        Movement _body_movement;
};

} // visual
} // gui

#endif
