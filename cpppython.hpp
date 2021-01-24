#ifndef CPPPYTHON
#define CPPPYTHON

#include <iostream>
#include <any>
#include <vector>
#include <string>
#include <typeinfo>

#define PY_SSIZE_T_CLEAN
#include <python3.8/Python.h>

template<typename T>
void func2(std::vector<std::pair<const char*, std::any>>& v, T arg){
    v.push_back({typeid(decltype(arg)).name(), arg});
}

template<typename T, typename ... Args>
void func1(std::vector<std::pair<const char*, std::any>>& v, T t, Args... args){
    func2(v, t);
    if constexpr(sizeof...(args) != 0){
        func1(v, args...);
    }
}

template<typename T, typename... Ts>
int call_python_function(T py_module_name, T py_function_name,Ts... arguments){
    std::vector<std::pair<const char*, std::any>> args;
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int nParams = sizeof...(arguments);

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(py_module_name);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, py_function_name);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(nParams);
            for(int i = 0; i <= nParams; ++i){
                pValue = PyLong_FromLong(4); // ??
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    std::cout << "Cannot convert argument\n";
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                //std::cout << "Result of call: " << PyLong_AsLong(pValue) << '\n';
                Py_DECREF(pValue);
                return PyLong_AsLong(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                std::cout << "Call failed\n";
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cout << "Cannot find function: " << py_function_name << '\n';
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        std::cout << "Failed to load: " <<  py_module_name << '\n';
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
#endif