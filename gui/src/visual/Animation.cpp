/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Animation.cpp
*/

#include "visual/Animation.hpp"

namespace gui {
namespace visual {

Animation::Animation(std::reference_wrapper<Drawable> drawable) : _draw(drawable)
{

}

void Animation::addAnimation(AnimationInfos infos)
{
    _animation.push_back(infos);
}

void Animation::addAnimation(const std::string& path, size_t frame_sizeX, size_t frame_sizeY,
    size_t frameX, size_t frameY, float delta, size_t indexX, size_t indexY)
{
    AnimationInfos infos;

    infos.clock.restart();
    infos.frame_size = sf::Vector2u(frame_sizeX, frame_sizeY);
    infos.max_frame = sf::Vector2u(frameX, frameY);
    infos.index = sf::Vector2u(indexX, indexY);
    infos.delta = delta;
    infos.path = path;
    _animation.push_back(infos);
}

void Animation::changeAnimation(int index)
{
    if (index >= static_cast<int>(_animation.size()) && index < NO_ANIM)
        return;
    _anim_index = index;
    if (_anim_index == NO_ANIM)
        return;
    _draw.get().texture.loadFromFile(A_SELECT.path);
    _draw.get().sprite.setTexture(_draw.get().texture);
    A_SELECT.index.x = 0;
    A_SELECT.index.y = 0;
    A_SELECT.clock.restart();
    _draw.get().sprite.setTextureRect(SET_RECT);
}

void Animation::animate()
{
    if (A_SELECT.clock.getElapsedTime().asSeconds() > A_SELECT.delta) {
        A_SELECT.index.x += 1;
        if (A_SELECT.index.x >= A_SELECT.max_frame.x) {
            A_SELECT.index.x = 0;
            A_SELECT.index.y += 1;
            if (A_SELECT.index.y >= A_SELECT.max_frame.y)
                A_SELECT.index.y = 0;
        }
        _draw.get().sprite.setTextureRect(SET_RECT);
        A_SELECT.clock.restart();
    }
}

}
}
