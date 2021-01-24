#include "cpppython.hpp"

int main()
{
    std::vector<std::pair<const char*, std::any>> vec;
    func1(vec, 1, 5.6, "hello");
    std::cout << vec[0].first << " " << std::any_cast<int>(vec[0].second) << '\n';
    std::cout << vec[1].first << " " << std::any_cast<double>(vec[1].second) << '\n';
    std::cout << vec[2].first << " " << std::any_cast<const char *>(vec[2].second) << '\n';
    std::cout << vec.size() << '\n';
    return 0;
}