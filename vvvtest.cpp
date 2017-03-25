#include "vvvtest.h"
#include <vector>


namespace __test_private {
std::vector<test_func_t>& __tests_registred()
{
    static std::vector<test_func_t> tests;
    return tests;
}

__test_register::__test_register(test_func_t func)
{
    __tests_registred().push_back(func); 
}
}

bool testall()
{
    const std::vector<test_func_t>& tests = __test_private::__tests_registred();
    int ret = 0;
    for(size_t i = 0; i < tests.size(); ++i) {
        ret += tests[i]();
    }
    return ret == 0;
}
