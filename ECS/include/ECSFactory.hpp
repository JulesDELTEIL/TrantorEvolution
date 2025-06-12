/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** ECSFactory.hpp
*/

#ifndef VISUAL_FACTORY_HPP_
    #define VISUAL_FACTORY_HPP_

    #include <map>
    #include <memory>

    #include "PluginManager.hpp"
    #include "interfaces/IEntity.hpp"
    #include "interfaces/IDrawable.hpp"

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
            void * handler = NULL;
            std::unique_ptr<Type>(*maker)(Args...) = NULL;
            handler = PluginManager::getHandler(object);
            if (handler == NULL) {
                return defaultObject<Type>();
            }
            maker = (std::unique_ptr<Type>(*)(Args...))dlsym(handler, (object + ENTRYPOINT).c_str());
            if (maker  == NULL)
                return defaultObject<Type>();
            return maker(args...);
        };

    private:

        template<typename Type>
        static std::unique_ptr<Type> defaultObject() {
            void* handler = PluginManager::getHandler("default");
            std::unique_ptr<Type>(*maker)(float, float) = NULL;
            std::string entrypoint;

            if (IS_TYPE(Type, IDrawable))
                entrypoint = "drawable" + ENTRYPOINT;
            else
                entrypoint = "entity" + ENTRYPOINT;
            maker = (std::unique_ptr<Type>(*)(float, float))dlsym(handler, entrypoint.c_str());
            return maker(0.0f, 0.0f);
        }

};

} // ecs

#endif
