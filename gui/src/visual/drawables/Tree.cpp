/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tree.cpp
*/

#include "visual/drawables/Tree.hpp"

namespace gui {
namespace visual {

Tree::Tree(const sf::Vector2f& pos) : AObject(pos, TREE_TEXTURE)
{
    _sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
    _sprite.setScale(sf::Vector2f(0.4, 0.4));
    _sprite.setOrigin(sf::Vector2f(15, 30));
}

} // visual
} // gui
