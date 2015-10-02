#include "./utils/test_utils.hpp"
#include <vrm/pp/for_each.hpp>

int main()
{
    int k{0};

#define TEST_MACRO_FOREFFECT(mIdx, mData, mArg) \
    k += mIdx;                                  \
    k += mArg;
    VRM_PP_FOREACH_REVERSE(TEST_MACRO_FOREFFECT, VRM_PP_EMPTY(), 1, 2, 3, 4)

    VRM_PP_FOREACH_REVERSE(TEST_MACRO_FOREFFECT, VRM_PP_EMPTY(), 0)
#undef TEST_MACRO_FOREFFECT

    TEST_ASSERT(k == 16);
    return 0;
}