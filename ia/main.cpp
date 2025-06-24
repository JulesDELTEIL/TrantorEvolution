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
    wchar_t **wargv = static_cast<wchar_t **>(PyMem_RawMalloc(sizeof(wchar_t *) * ac));
    for (unsigned int i = 0; i < static_cast<unsigned int>(ac); ++i) {
        wargv[i] = Py_DecodeLocale(av[i], nullptr);
        if (!wargv[i])
            return PROJECT_ERROR;
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
    std::string projectDir = static_cast<std::string>(dirname(av[0])) + "/ia/python";
    std::string pythonMainPath = projectDir + "/__main__.py";
    std::string code = "import sys\n"
                        "sys.path.insert(0, \"" + projectDir + "\")\n";
    PyRun_SimpleString(code.c_str());
    FILE *fp = fopen(pythonMainPath.c_str(), "r");
    if (!fp) {
        std::cerr << "Can't open " << pythonMainPath << std::endl;
        Py_Finalize();
        return PROJECT_ERROR;
    }
    int returnVal = PyRun_SimpleFile(fp, "__main__.py");
    fclose(fp);
    if (PyErr_Occurred())
        PyErr_Print();
    Py_Finalize();
    return returnVal;
}