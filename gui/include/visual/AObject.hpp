/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AObject.hpp
*/

#ifndef AObject_HPP_
    #define AObject_HPP_

    #include <string>

    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/System/Clock.hpp>

    #include "visual/ADrawable.hpp"

namespace gui {
namespace visual {

class AObject : public ADrawable, public sf::Sprite {
    public:
        AObject(const sf::Vector2f&);
        ~AObject() = default;

    protected:
        sf::Texture _texture;

};


} // visual
} // gui

#endif
