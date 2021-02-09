#include "cpppython.hpp"



int main()
{
    //CppInstance pyinstance;
    std::cout << call_python_function("test_python", "sum", "sda", "sadkm", "asdkq") << '\n';
    std::cout << "hello" << '\n';
    return 0;
}