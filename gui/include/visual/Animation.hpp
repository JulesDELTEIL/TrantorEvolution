/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Animation.hpp
*/

#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

    #include <string>
    #include <vector>
    #include <SFML/System/Clock.hpp>

    #include "visual/Drawable.hpp"

namespace gui {
namespace visual {

struct AnimationInfos {
    std::string path;
    sf::Vector2u frame_size;
    sf::Vector2u max_frame;
    sf::Vector2u index;
    float delta;
    sf::Clock clock;
};

    #define NO_ANIM -1
    #define A_SELECT (this->_animation[this->_anim_index])
    #define SET_RECT (sf::IntRect(A_SELECT.frame_size.x * A_SELECT.index.x, A_SELECT.frame_size.y * A_SELECT.index.y, A_SELECT.frame_size.x, A_SELECT.frame_size.y))

class Animation {
    public:
        Animation(std::reference_wrapper<Drawable>);
        ~Animation() = default;

        void addAnimation(AnimationInfos);
        void addAnimation(const std::string&, size_t, size_t,
            size_t, size_t, float, size_t indexX = 0, size_t indexY = 0);
        void changeAnimation(int index);
        void animate();

    protected:
        int _anim_index = 0;
        std::vector<AnimationInfos> _animation;
        std::reference_wrapper<Drawable> _draw;

};

} // visual
} // gui

#endif
