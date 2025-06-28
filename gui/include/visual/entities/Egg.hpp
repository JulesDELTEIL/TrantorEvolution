/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg.hpp
*/

#ifndef EGG_HPP_
    #define EGG_HPP_

    #include <SFML/Graphics/RenderTarget.hpp>

    #include "visual/Drawable.hpp"
    #include "visual/Animation.hpp"

namespace gui {
namespace visual {

static const AnimationInfos EGG_ANIM_INFO = {
    "assets/object/Egg-Sheet.png",
    {64, 64},
    {4, 1},
    {0, 0},
    0.5,
    sf::Clock()
};

class Egg {
    public:
        Egg(const sf::Vector2f&);
        ~Egg() = default;

        void draw(sf::RenderTarget&);
        void hatch();
    private:
        Drawable _egg;
        sf::Clock _clock;
        bool _hatching;
        sf::IntRect _rect;
};

} // gui
} // visual
#endif