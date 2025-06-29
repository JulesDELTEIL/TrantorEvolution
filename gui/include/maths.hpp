/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** hitbox.hpp
*/

#ifndef HITBOX_HPP_
    #define HITBOX_HPP_

    #include <SFML/System/Vector2.hpp>
    #include <SFML/Graphics/Rect.hpp>

bool hitTriangle(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
bool hitRectangle(const sf::Vector2i&, const sf::IntRect&);

#endif