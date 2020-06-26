#include "cpppython.hpp"
#include <string>


int main()
{
    int result = call_python_function("module.py", "sum", 4,3);
    return 0;
}