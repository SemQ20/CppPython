#include "cpppython.hpp"

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

//void exitPython(){
 //   Py_FinalizeEx();
//}

