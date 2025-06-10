/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ADrawable.hpp
*/

#ifndef ADRAWABLE_HPP_
    #define ADRAWABLE_HPP_

    #include "visual/IDrawable.hpp"

namespace gui {
namespace visual {

class ADrawable : public IDrawable {
    public:
        ADrawable(sf::Vector2f entity_origin);
        ~ADrawable() = default;

        VisualType_e getId(void) override;

        void setPosition(const sf::Vector2f&) override;
        sf::Vector2f getPosition(void) const override;
        void setRotation(float) override;
        float getRotation(void) const override;

    protected:
        sf::Vector2f _pos;
        float _angle;
        VisualType_e _type = DRAWABLE;
};

} // visual
} // gui

#endif
