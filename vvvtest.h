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


#define __PASTER(x, y) x##y
#define __EVALUATOR(x, y) __PASTER(x, y)
#define __VVVTEST_EQ(name, expr) \
namespace { \
int name() \
{\
    printf("test: " #expr " ... ");\
    if((expr)) {printf("passed.\n"); return  0;} \
    else       {printf("failed.\n"); return -1;} \
} \
\
__test_private::__test_register __EVALUATOR(name,object) = \
                        __test_private::__test_register(name); \
\
}
#define __NAME(x) __EVALUATOR(x, __LINE__)
#define __NAME_(expr) __VVVTEST_EQ(__NAME(__vvvtest_), expr)
#define VVVTEST_EQ(expr) __NAME_(expr)



#endif

