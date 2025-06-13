/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** DefaultScene.cpp
*/

#include "visual/scenes/DefaultScene.hpp"
#include "core/Engine.hpp"

#include "visual/layers/DefaultLayer.hpp"

namespace gui {
namespace visual {

DefaultScene::DefaultScene() : AScene(core::DEFAULT_VIEW)
{
    _layers.emplace_back(std::make_unique<DefaultLayer>());
}

void DefaultScene::display(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<ILayer>& layer : _layers) {
        layer->display(target);
    }
}

void DefaultScene::event(const sf::Event& event)
{
    for (std::unique_ptr<ILayer>& layer : _layers) {
        layer->event(event);
    }
}

} // visual
} // gui
