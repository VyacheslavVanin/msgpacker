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


#define PASTER(x, y) x##y
#define EVALUATOR(x, y) PASTER(x, y)
#define VVVTEST_EQ_(name, expr) \
namespace { \
int name() \
{\
    printf("test: " #expr " ... ");\
    if((expr)) {printf("passed.\n"); return  0;} \
    else       {printf("failed.\n"); return -1;} \
} \
\
__test_private::__test_register EVALUATOR(name,object) = \
                        __test_private::__test_register(name); \
\
}
#define NAME(x) EVALUATOR(x, __LINE__)
#define NAME_(expr) VVVTEST_EQ_(NAME(__vvvtest_), expr)
#define VVVTEST_EQ(expr) NAME_(expr)



#endif

