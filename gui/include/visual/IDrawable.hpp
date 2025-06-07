/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP_
    #define IDRAWABLE_HPP_

    #include <SFML/Graphics/Drawable.hpp>
    #include <SFML/Graphics/Transformable.hpp>

    #include "visual/visual.hpp"

namespace gui {
namespace visual {

class IDrawable : public sf::Drawable, public sf::Transformable {
    public:
        virtual VisualType_e getId(void) = 0;

};

} // visual
} // gui

#endif