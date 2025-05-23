#ifndef VVVTEST_H
#define VVVTEST_H
#include <vector>
#include <stdlib.h>

struct __TesterBase {
    __TesterBase(std::vector<const __TesterBase*>& tests) {
        tests.push_back(this);
    }
    virtual int test() const = 0;
    virtual ~__TesterBase() {};
};

bool testall(const std::vector<const __TesterBase*>&);

namespace {
    std::vector<const __TesterBase*> tests;

    template <int N>
    struct __Tester;

    inline bool testall() {
        return testall(tests);
    }
}

#define __PASTER(x, y) x##y
#define __EVALUATOR(x, y) __PASTER(x, y)

#define __VVVTEST_EQ(line, expr) \
namespace { \
template <> struct __Tester<line> : __TesterBase { \
    __Tester(std::vector<const __TesterBase*>& tests) : __TesterBase(tests) {} \
    int test() const { \
        printf("test: " #expr " ... "); \
        if((expr)) {printf("passed.\n"); return  0;} \
        else       {printf("failed.\n"); return -1;} \
    } \
}; \
__Tester<line> __EVALUATOR(__vvvtest_,line) (tests); \
}

#define VVVTEST_EQ(expr) __VVVTEST_EQ(__LINE__,expr)

#endif

