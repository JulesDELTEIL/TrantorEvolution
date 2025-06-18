/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultDrawable.hpp
*/

#ifndef DEFAULT_ENTITY_HPP
    #define DEFAULT_ENTITY_HPP

    #include <memory>

    #include "interfaces/AEntity.hpp"

namespace ecs {
    
class DefaultEntity : public AEntity {
    public:
        DefaultEntity(float x, float y, ...);
        ~DefaultEntity() = default;

        void display(sf::RenderTarget& render) const override;
        void event(int event) override;

};

} // namespace ecs

#endif
