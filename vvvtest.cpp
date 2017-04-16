#include "vvvtest.h"

bool testall(const std::vector<const __TesterBase*>& tests) {
    int ret = 0;
    for(size_t i = 0; i < tests.size(); ++i) {
        ret += tests[i]->test();
    }
    return ret == 0;
}
