/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include "visual/IScene.hpp"

namespace gui {
namespace visual {

class AScene : public IScene {
    public:
        AScene(const sf::FloatRect&);
        ~AScene() = default;

        void display(sf::RenderTarget&) = 0;
        void event(const core::Engine&, const network::NetEventPack&) = 0;

        sf::View getView(void) override;
        sf::Vector2f getViewPos(void) const override;

        bool changeViewDest(const sf::Vector2f&, float) override;
        bool moveToDest(void) override;

        void zoom(float) override;
        void move(const sf::Vector2f&) override;
        void move(float, float) override;

    protected:
        float _zoom = 1;
        sf::View _camera;
        sf::Clock _clock;

        sf::Vector2f _direction;
        float _time;
        float _start;
        float _last_time;

};

} // visual
} // gui

#endif
