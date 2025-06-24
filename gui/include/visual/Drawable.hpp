/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Drawable.hpp
*/

#ifndef DRAWABLE_HPP_
    #define DRAWABLE_HPP_

    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/Graphics/Sprite.hpp>

namespace gui {
namespace visual {

struct Drawable {
    sf::Sprite sprite;
    sf::Texture texture;
};

}
}

#endif
