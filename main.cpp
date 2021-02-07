#include "cpppython.hpp"



int main()
{
    //int result = call_python_function("test_python", "sum", 4, 3, 5);
    std::cout << call_python_function("test_python", "sum", "suc", "sdmi", "askd") << '\n';
    return 0;
}