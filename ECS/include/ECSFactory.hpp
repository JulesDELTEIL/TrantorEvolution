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
    #include <functional>

    #include "PluginManager.hpp"
    #include "interfaces/IEntity.hpp"
    #include "interfaces/IDrawable.hpp"

namespace ecs {

class ECSFactory {
    public:
        ECSFactory() = delete;
        ~ECSFactory() = default;

        ECSFactory(const ECSFactory&) = delete;
        void operator=(const ECSFactory&) = delete;

        template<typename Type, typename ...Args>
        static std::unique_ptr<Type> create(const std::string& entity, Args... args) {
            void * handler = NULL;
            std::unique_ptr<Type>(*maker)(Args...) = NULL;
            handler = PluginManager::getHandler(entity);
            if (handler == NULL) {
                throw std::invalid_argument(entity + " not found");
            }
            maker = (std::unique_ptr<Type>(*)(Args...))dlsym(handler, (entity + ENTRYPOINT).c_str());
            if (maker  == NULL)
                throw std::invalid_argument("can't load " + entity);
            return maker(args...);
        };

    private:

};

} // ecs

#endif
