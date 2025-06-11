/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AAnimated.cpp
*/

#include "interfaces/AAnimated.hpp"

namespace ecs {

AAnimated::AAnimated(const sf::Vector2f& pos, const std::string& path, const sf::IntRect& rect) :
    AObject(pos, path, rect)
{

}

void AAnimated::restartClock(void)
{
    _anim_clock.restart();
}

} // ecs
