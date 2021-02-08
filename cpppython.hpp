#ifndef CPPPYTHON
#define CPPPYTHON

#include <iostream>
#include <any>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>

#define PY_SSIZE_T_CLEAN
#include <python3.8/Python.h>

template<typename T>
void helper_func_unpack_params(std::vector<std::pair<const char*, std::any>>& v, T arg){
    v.push_back({typeid(decltype(arg)).name(), arg});
}

template<typename T, typename ... Args>
void unpack_params(std::vector<std::pair<const char*, std::any>>& v, T t, Args... args){
    helper_func_unpack_params(v, t);
    if constexpr(sizeof...(args) != 0){
        unpack_params(v, args...);
    }
}

template<typename T>
void helper_free_mem(T *t){
    Py_DECREF(t);
}

template<typename T, typename... Args>
void Py_free_mem(T *t, Args... args){
    helper_free_mem(t);
    if constexpr(sizeof...(args) != 0){
        Py_free_mem(args...);
    }
}

PyObject* get_Values_For_Function_Call(std::vector<std::pair<const char*, std::any>> vec, int iteration, int num_params){
    PyObject *obj;
    if(iteration <= num_params){
        if(vec[iteration].first == typeid(const char*).name()){
            obj = PyUnicode_DecodeFSDefault(std::any_cast<const char*>(vec[iteration].second));
        }
        if(vec[iteration].first == typeid(int).name()){
            obj = PyLong_FromLong(std::any_cast<int>(vec[iteration].second));
        }
        if(vec[iteration].first == typeid(float).name()){
            obj = PyFloat_FromDouble(std::any_cast<float>(vec[iteration].second));
        }
        if(vec[iteration].first == typeid(double).name()){
            obj = PyFloat_FromDouble(std::any_cast<double>(vec[iteration].second));
        }
    }else{
        return obj = nullptr;
    }
    return obj;
}

//type deduction problem
template<typename T, typename... Ts>
const char* call_python_function(T py_module_name, T py_function_name,Ts... arguments){
    std::vector<std::pair<const char*, std::any>> args;
    unpack_params(args,arguments...);
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    int nParams = sizeof...(arguments) - 1;
    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(py_module_name);
    /* Error checking of pName left out */
    pModule = PyImport_Import(pName);
    Py_free_mem(pName);
    const char *result;
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, py_function_name);
        /* pFunc is a new reference */
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(nParams + 1);
            for(int i = 0; i <= nParams; i++){
                pValue = get_Values_For_Function_Call(args, i, nParams);
                if (!pValue) {
                    Py_free_mem(pArgs, pModule);
                    /* TODO: add abstract exception */
                    std::cout << "Cannot convert argument\n";
                    return "1";
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_free_mem(pArgs);
            if (pValue != NULL) {
                Py_free_mem(pValue);
                return PyUnicode_AsUTF8(pValue); // ?????????
            }
            else {
                Py_free_mem(pFunc, pModule);
                PyErr_Print();
                std::cout << "Call failed\n";
                return "1";
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cout << "Cannot find function: " << py_function_name << '\n';
        }
        Py_XDECREF(pFunc);
        Py_free_mem(pModule);
    }
    else {
        PyErr_Print();
        std::cout << "Failed to load: " <<  py_module_name << '\n';
        return "1";
    }
    if (Py_FinalizeEx() < 0) {
        return "120";
    }
    return "0";
}
#endif