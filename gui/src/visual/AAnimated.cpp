/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AAnimated.cpp
*/

#include "visual/AAnimated.hpp"

namespace gui {
namespace visual {

AAnimated::AAnimated(const sf::Vector2f& entity_pos,
    const std::string& sprite_path) : AObject(entity_pos, sprite_path)
{

}

void AAnimated::restartClock(void)
{
    _anim_clock.restart();
}

} // visual
} // gui
