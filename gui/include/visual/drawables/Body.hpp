/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Body.hpp
*/

#ifndef BODY_HPP_
    #define BODY_HPP_

    #include "interfaces/AAnimated.hpp"

namespace gui {
namespace visual {

enum BodyAnimIndex {
    IDLE = 0,
    WALK,
    COLLECT,
};

    #define NB_BODY_ANIM 3

static const std::vector<ecs::AnimationInfos> BODY_ANIM_INFOS = {
    {"assets/trantorians/body/Idle_Side-Sheet.png", {64, 64}, {4, 1}, {0, 0}, 0.3, sf::Clock()},
    {"assets/trantorians/body/Walk_Side-Sheet.png", {64, 64}, {6, 1}, {0, 0}, 0.1, sf::Clock()},
    {"assets/trantorians/body/Collect_Side-Sheet.png", {64, 64}, {8, 1}, {0, 0}, 0.2, sf::Clock()}
};

class Body : public ecs::AAnimated {
    public:
        Body(const sf::Vector2f&);
        ~Body() = default;

};

} // visual
} // gui


#endif