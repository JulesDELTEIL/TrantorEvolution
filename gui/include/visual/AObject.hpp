/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AObject.hpp
*/

#ifndef AOBJECT_HPP_
    #define AOBJECT_HPP_

    #include <string>

    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/Graphics/Rect.hpp>
    #include "visual/ADrawable.hpp"

namespace gui {
namespace visual {

class AObject : public ADrawable {
    public:
        AObject(const sf::Vector2f& pos, const std::string& path,
            const sf::IntRect& rect = sf::IntRect());
        ~AObject() = default;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setPosition(const sf::Vector2f& pos) override;
        sf::Vector2f getPosition(void) const override;
        void setRotation(float angle) override;
        float getRotation(void) const override;

    protected:
        sf::Texture _texture;
        sf::Sprite _sprite;
};


} // visual
} // gui

#endif
