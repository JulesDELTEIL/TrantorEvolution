/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultDrawable.hpp
*/

#ifndef DEFAULT_DRAWABLE_HPP_
    #define DEFAULT_DRAWABLE_HPP_

    #include <memory>

    #include "interfaces/AObject.hpp"

    #define DEFAULT_TEXTURE "ECS/assets/error.png"
    #define DEFAULT_TEXTURE_RECT sf::IntRect(0, 0, 800, 800)

namespace ecs {
    
class DefaultDrawable : public AObject {
    public:
        DefaultDrawable(float x, float y, ...);
        ~DefaultDrawable() = default;

};

} // namespace ecs

#endif
