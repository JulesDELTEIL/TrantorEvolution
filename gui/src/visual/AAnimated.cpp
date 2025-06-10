/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AAnimated.cpp
*/

#include "visual/AAnimated.hpp"

namespace gui {
namespace visual {

AAnimated::AAnimated(const sf::Vector2f& pos, const std::string& path) :
    AObject(pos, path)
{

}

void AAnimated::restartClock(void)
{
    _anim_clock.restart();
}

} // visual
} // gui
