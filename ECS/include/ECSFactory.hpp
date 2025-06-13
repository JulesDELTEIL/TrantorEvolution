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

    #define DRAW_ENTRY ("drawable" + ENTRYPOINT)
    #define ENTITY_ENTRY ("entity" + ENTRYPOINT)

    #define IS_TYPE(t1, t2) (typeid(t1) == typeid(t2))

namespace ecs {

class ECSFactory {
    public:
        ECSFactory() = delete;
        ~ECSFactory() = default;

        ECSFactory(const ECSFactory&) = delete;
        void operator=(const ECSFactory&) = delete;

        template<typename Type, typename ...Args>
        static std::unique_ptr<Type> create(const std::string& object, Args... args) {
            if (IS_TYPE(Type, IEntity)) {
                if (_entities.find(object) == _entities.end())
                    return std::make_unique<DefaultEntity>(0, 0);
                return _entities.at(object)(args...);
            } else {
                if (_drawables.find(object) == _drawables.end())
                    return std::make_unique<DefaultDrawable>(0, 0);
                return _drawables.at(object)(args...);
            }
        };

    private:
        typedef std::function<std::unique_ptr<IEntity>()>  entityMaker;
        static inline const std::map<std::string, entityMaker> _entities = {

        };

        typedef std::function<std::unique_ptr<IEntity>()> drawMaker;
        static inline const std::map<std::string, drawMaker> _drawables = {
            
        };

};

} // ecs

#endif
