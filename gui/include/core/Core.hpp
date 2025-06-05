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
    #include "visual/IMenu.hpp"

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

        std::map<visual::MenuType_e, std::unique_ptr<visual::IMenu>> _menus;

};

} // core
} // core

#endif
