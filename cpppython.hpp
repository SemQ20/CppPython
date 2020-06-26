#ifndef CPPPYTHON
#define CPPPYTHON

#include <iostream>
#include <deque>

#define PY_SSIZE_T_CLEAN
#include <python3.8/Python.h>

#if defined (_WIN32)
#include <Python.h>
#endif 

template<typename T, typename... Ts>
int call_python_function(T py_module_name, T py_function_name,Ts... arguments){
    std::deque<Ts...> cont{arguments...};
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
            pArgs = PyTuple_New(sizeof...(arguments));
            for(int i = 0; i <= cont.size(); ++i){
                pValue = PyLong_FromLong(cont.front());
                cont.pop();

                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    std::cout << "Cannot convert argument\n";
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, nParams, pValue);
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