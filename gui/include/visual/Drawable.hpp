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
    #include <string>

namespace gui {
namespace visual {

struct Drawable {
    Drawable() = default;
    Drawable(const std::string&, float scale = 1.0f);
    sf::Sprite sprite;
    sf::Texture texture;
};

}
}

#endif
