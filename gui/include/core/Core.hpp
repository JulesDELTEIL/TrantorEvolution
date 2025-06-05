/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Core.hpp
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <map>

    #include "core/Engine.hpp"

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

};

} // core
} // core

#endif
