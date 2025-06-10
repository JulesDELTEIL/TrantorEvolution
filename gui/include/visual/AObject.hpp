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

    #include "visual/ADrawable.hpp"

namespace gui {
namespace visual {

class AObject : public ADrawable {
    public:
        AObject(const sf::Vector2f&, const std::string&);
        ~AObject() = default;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setPosition(const sf::Vector2f&) override;
        sf::Vector2f getPosition(void) const override;
        void setRotation(float) override;
        float getRotation(void) const override;

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;

};


} // visual
} // gui

#endif
