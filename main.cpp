#include "cpppython.hpp"

int main()
{
    int result = call_python_function("test_python", "sum", 4, 3);
    std::cout << result << '\n';
    return 0;
}