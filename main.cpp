#include "cpppython.hpp"



int main()
{
    //int result = call_python_function("test_python", "sum", 4, 3, 5);
    std::cout << call_python_function("test_python", "sum" ,3.1, 4.3, 1.3) << '\n';
    return 0;
}