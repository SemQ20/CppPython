#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CppPython

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "../cpppython.hpp"


BOOST_AUTO_TEST_CASE(substract_Test){
    std::string s = call_python_function("test_python", "sum" ,"sddsa", "asek", "asdiqw");
    BOOST_CHECK(s == "sddsaasekasdiqw");
}
