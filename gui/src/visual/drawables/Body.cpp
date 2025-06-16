/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Body.cpp
*/

#include "visual/drawables/Body.hpp"

namespace gui {
namespace visual {

Body::Body(const sf::Vector2f& pos) : AAnimated(pos, "", sf::IntRect(0, 0, 0, 0))
{
    for (const ecs::AnimationInfos& info : BODY_ANIM_INFOS)
        addAnimation(info);
    changeAnimation(WALK);
    _sprite.setScale(0.2, 0.2);
}

} // visual
} // gui
