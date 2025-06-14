/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.hpp
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <map>
    #include <memory>

    #include "core/Engine.hpp"
    #include "visual/visual.hpp"
    #include "visual/IScene.hpp"

    #include "ECSFactory.hpp"
    #include "visual/setup.hpp"

namespace gui {
namespace core {

class Core {
    public:
        Core();
        ~Core() = default;

        void run(void);

    private:
        Engine _engine;

        void display(void);
        void events(void);

        visual::Scene_e _selected_scene;
        std::map<visual::Scene_e, std::unique_ptr<visual::IScene>> _scenes;
        void changeScene(const visual::Scene_e&);

        void setupVisual(void);
};

} // core
} // core

#endif
