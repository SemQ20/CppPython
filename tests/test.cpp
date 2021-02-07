#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CppPython

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "../cpppython.hpp"


BOOST_AUTO_TEST_CASE(substract_Test){
    BOOST_CHECK(std::round(call_python_function("test_python", "sum" ,3.1, 4.3, 1.3)) == std::round(8.7));
}
