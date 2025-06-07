/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultScene.cpp
*/

#include "visual/scenes/DefaultScene.hpp"
#include "visual/layers/DefaultLayer.hpp"

namespace gui {
namespace visual {

DefaultScene::DefaultScene() : AScene()
{
    _layers.emplace_back(std::make_unique<DefaultLayer>());
}

} // visual
} // gui
