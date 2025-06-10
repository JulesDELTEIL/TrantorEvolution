/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Tree.hpp
*/

#ifndef TREE_HPP_
    #define TREE_HPP_

    #include "visual/AObject.hpp"

    #define TREE_TEXTURE "assets/ressources/Grass_Biom_Tree.png"

namespace gui {
namespace visual {

class Tree : public AObject {
    public:
        Tree(const sf::Vector2f& pos);
        ~Tree() = default;

    private:

};

} // visual
} // gui

#endif
