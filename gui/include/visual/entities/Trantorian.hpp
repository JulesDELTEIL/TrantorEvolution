/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Trantorian.hpp
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>

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
        Trantorian(const sf::Vector2f& pos);
        ~Trantorian() = default;

        void draw(sf::RenderTarget&);
        void collect(void);
        void move(const sf::Vector2f&, float);

    private:
        Drawable _body;
        Animation _body_animation;
        Movement _body_movement;
};

} // visual
} // gui

#endif
