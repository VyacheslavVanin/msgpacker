#ifndef VVVTEST_H
#define VVVTEST_H
#include <vector>
#include <stdlib.h>

bool testall();



typedef int (*test_func_t)();

namespace __test_private {

class __test_register
{
    public:
        __test_register(test_func_t func);
};
}

#define VVVTEST_EQ(name, expr) \
int name() \
{\
    printf("test: " #expr " ... ");\
    if((expr)) {printf("passed.\n"); return  0;} \
    else       {printf("failed.\n"); return -1;} \
} \
namespace __test_private { \
__test_register name##object = __test_register(name); \
}

#endif

