/*
** EPITECH PROJECT, 2024
** TrantorEvolution
** File description:
** main.cpp
*/

#include <Python.h>
#include <iostream>
#include <libgen.h>
#include <string>
#include <cstring>

#include "../include/project_tools.h"

int main(int ac, char **av) {
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    wchar_t **wargv = static_cast<wchar_t**>(
        PyMem_RawMalloc(sizeof(wchar_t*) * ac)
    );
    for (int i = 0; i < ac; ++i) {
        wargv[i] = Py_DecodeLocale(av[i], nullptr);
        if (!wargv[i]) return PROJECT_ERROR;
    }
    config.argv.length = ac;
    config.argv.items = wargv;
    config.parse_argv = 0;
    status = Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);
    if (PyStatus_Exception(status)) {
        std::cerr << status.err_msg << std::endl;
        return PROJECT_ERROR;
    }
    char *copy = strdup(av[0]);
    std::string dir = dirname(copy);
    free(copy);
    std::string path = dir + "/ia/python/__main__.py";
    std::string pkg_dir = dir + "/ia/python";
    std::string code = "import sys\n"
        "sys.path.insert(0, \"" + pkg_dir + "\")\n";
    PyRun_SimpleString(code.c_str());
    FILE *fp = fopen(path.c_str(), "r");
    if (!fp) {
        std::cerr << "Can't open " << path << std::endl;
        Py_Finalize();
        return PROJECT_ERROR;
    }
    int return_value = PyRun_SimpleFile(fp, "__main__.py");
    fclose(fp);
    if (PyErr_Occurred())
        PyErr_Print();
    Py_Finalize();
    return return_value;
}