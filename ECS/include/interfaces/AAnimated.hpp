/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AAnimated.hpp
*/

#ifndef AANIMATED_HPP_
    #define AANIMATED_HPP_

    #include <SFML/System/Clock.hpp>

    #include "interfaces/AObject.hpp"

namespace ecs {

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

class AAnimated : public AObject {
    public:
        AAnimated(const sf::Vector2f&, const std::string&, const sf::IntRect&);
        ~AAnimated() = default;

        void draw(sf::RenderTarget& target) override;

        void addAnimation(AnimationInfos);
        void addAnimation(const std::string&, size_t, size_t,
            size_t, size_t, float, size_t indexX = 0, size_t indexY = 0);
        void changeAnimation(int index);
        void animate(void);

    protected:
        int _anim_index;
        std::vector<AnimationInfos> _animation;

};

} // ecs

#endif
