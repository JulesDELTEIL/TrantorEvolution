/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** PluginManager.hpp
*/

#ifndef PLUGIN_MANAGER_HPP_
    #define PLUGIN_MANAGER_HPP_

    #include <dlfcn.h>

    #include <map>
    #include <string>
    #include <filesystem>
    #include <iostream>

    #define DEFAULT_PATH "ECS/default.so"

    #define LAST_SLASH(s) (s.find_last_of("/\\") + 1)
    #define DL_EXTENSION ".so"
    #define DL_EXTENSION_SIZE 3
    #define GET_PLUGIN_NAME(s) s.substr(LAST_SLASH(s), s.size() - LAST_SLASH(s) - DL_EXTENSION_SIZE);

static const std::string ENTRYPOINT = "Entrypoint";

class PluginManager {
    public:
        PluginManager() = delete;
        ~PluginManager() {
            for (const auto& handle : _handlers) {
                if (handle.second != NULL)
                    dlclose(handle.second);
            }
        };

        PluginManager(const PluginManager&) = delete;
        void operator=(const PluginManager&) = delete;

        static void load(void) {
            setHandler(DEFAULT_PATH);
        }

        static void load(const std::string& path) {
            setHandler(DEFAULT_PATH);
            for (const auto &file : std::filesystem::directory_iterator(path)) {
                if (!std::filesystem::path(file).extension().compare(DL_EXTENSION)) {
                    setHandler(file.path());
                }
            }
        };

        static void *getHandler(const std::string& id) {
            if (_handlers.find(id) == _handlers.end())
                return NULL;
            return _handlers.at(id);
        }

    private:
        static inline std::map<std::string, void*> _handlers;

        static void setHandler(const std::string& path) {
            void *handle = NULL;
            std::string pluginName;

            handle = dlopen(path.c_str(), RTLD_LAZY);
            if (handle == NULL) {
                std::cerr << dlerror() << std::endl;
                return;
            }
            pluginName = GET_PLUGIN_NAME(path);
            _handlers[pluginName] = handle;
        }

};

#endif
