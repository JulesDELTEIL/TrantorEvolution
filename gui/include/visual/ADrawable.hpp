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

class ADrawable : public IDrawable{
    public:
        ADrawable(sf::Vector2f entity_origin);
        ~ADrawable() = default;
        VisualType_e getId(void) override;

    private:
        VisualType_e _type = DRAWABLE;
};

} // visual
} // gui

#endif
