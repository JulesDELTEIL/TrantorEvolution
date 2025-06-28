/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** hitbox.cpp
*/

#include "maths.hpp"

static float sign(const sf::Vector2f& p1,
    const sf::Vector2f& p2, const sf::Vector2f& p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool hitTriangle(const sf::Vector2f& hit, const sf::Vector2f& p1,
    const sf::Vector2f& p2, const sf::Vector2f& p3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(hit, p1, p2);
    d2 = sign(hit, p2, p3);
    d3 = sign(hit, p3, p1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}


bool hitRectangle(const sf::Vector2i& mpos, const sf::IntRect& rect)
{
    if (mpos.x >= rect.left && mpos.x <= rect.left + rect.width &&
        mpos.y >= rect.top && mpos.y <= rect.top + rect.height)
        return true;
    return false;
}
