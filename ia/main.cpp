/*
** EPITECH PROJECT, 2024
** TrantorEvolution
** File description:
** main.cpp
*/

#include <Python.h>
#include <iostream>
#include <vector>

#include "../include/project_tools.h"

int main(int ac, char **av) {
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    std::vector<wchar_t*> wargv(ac);
    for (unsigned int i = 0; i < static_cast<unsigned int>(ac); i++)
        wargv[i] = Py_DecodeLocale(av[i], nullptr);
    status = PyConfig_SetArgv(&config, ac, wargv.data());
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        std::cerr << "PyConfig_SetArgv error: " << status.err_msg << std::endl;
        return PROJECT_ERROR;
    }
    status = Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        std::cerr << "Python initialization error: " << status.err_msg << std::endl;
        return PROJECT_ERROR;
    }
    PyRun_SimpleString(
        "import sys\n" 
        "sys.path.insert(0, \"./ia/python\")\n");
    FILE *fp = fopen("ia/python/__main__.py", "r");
    if (!fp) {
        std::cerr << "Can't open 'python/__main__py'" << std::endl;
        Py_Finalize();
        return PROJECT_ERROR;
    }
    unsigned int return_value = PyRun_SimpleFile(fp, "__main__.py");
    fclose(fp);
    Py_Finalize();
    return return_value;
}