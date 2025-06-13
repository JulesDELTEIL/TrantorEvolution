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
    #include <SFML/Graphics/RenderTarget.hpp>

    #include "interfaces/ADrawable.hpp"

namespace ecs {

class AObject : public ADrawable {
    public:
        AObject(const sf::Vector2f& pos, const std::string& path,
            const sf::IntRect& rect);
        ~AObject() = default;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setPosition(const sf::Vector2f& pos) override;
        sf::Vector2f getPosition(void) const override;
        void setScale(const sf::Vector2f&) override;
        sf::Vector2f getScale(void) const override;
        void zoom(const sf::Vector2f&) override;

    protected:
        sf::Texture _texture;
        sf::Sprite _sprite;
};

} // ecs

#endif
