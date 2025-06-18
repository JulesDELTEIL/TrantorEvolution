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
    for (int i = NB_BODY_ANIM - 1; i >= 0; --i)
        addAnimation(BODY_ANIM_INFOS[i]);
    changeAnimation(WALK);
    _scale = {0.2, 0.2};
    _sprite.setScale(_scale.x, _scale.y);
}

} // visual
} // gui
