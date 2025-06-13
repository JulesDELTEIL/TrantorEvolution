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

class AAnimated : public AObject {
    public:
        AAnimated(const sf::Vector2f&, const std::string&, const sf::IntRect&);
        ~AAnimated() = default;

        virtual void animation(void) = 0;
        void restartClock(void);

    protected:
        size_t _anim_index;
        float _anim_delta;
        sf::Clock _anim_clock;

};

} // ecs

#endif
