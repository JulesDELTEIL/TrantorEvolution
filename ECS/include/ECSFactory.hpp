/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ECSFactory.hpp
*/

#ifndef ECS_FACTORY_HPP_
    #define ECS_FACTORY_HPP_

    #include <memory>
    #include <map>
    #include <functional>

    #include "interfaces/IEntity.hpp"
    #include "interfaces/IDrawable.hpp"

    #include "default/DefaultDrawable.hpp"
    #include "default/DefaultEntity.hpp"

    #define DEFAULT_ID "default"

    #define IS_TYPE(t1, t2) (typeid(t1) == typeid(t2))

namespace ecs {

class ECSFactory {
    public:
        ECSFactory() = delete;
        ~ECSFactory() = default;

        ECSFactory(const ECSFactory&) = delete;
        void operator=(const ECSFactory&) = delete;

        template<typename ...Args>
        static void setDraw(const std::string& object, std::unique_ptr<IDrawable>(*maker)(Args...)) {
            if (_drawables<Args...>.find(object) == _drawables<Args...>.end())
                _drawables<Args...>[object] = maker;
        }

        template<typename ...Args>
        static std::unique_ptr<IDrawable> createDraw(const std::string& object, Args... args) {
            if (_drawables<Args...>.find(object) == _drawables<Args...>.end())
                return std::make_unique<DefaultDrawable>(args...);
            return _drawables<Args...>.at(object)(args...);
        };

        template<typename ...Args>
        static void setEntity(const std::string& object, std::unique_ptr<IEntity>(*maker)(Args...)) {
            if (_entities<Args...>.find(object) == _entities<Args...>.end())
                _entities<Args...>[object] = maker;
        }

        template<typename ...Args>
        static std::unique_ptr<IEntity> createEntity(const std::string& object, Args... args) {
            if (_entities<Args...>.find(object) == _entities<Args...>.end())
                return std::make_unique<DefaultEntity>(args...);
            return _entities<Args...>.at(object)(args...);
        };

    private:

        template<typename ...Args>
        static inline std::map<std::string, std::unique_ptr<IEntity>(*)(Args...)> _entities = {};

        template<typename ...Args>
        static inline std::map<std::string, std::unique_ptr<IDrawable>(*)(Args...)> _drawables = {};

};

} // ecs

#endif
