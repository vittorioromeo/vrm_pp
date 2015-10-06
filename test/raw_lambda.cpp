#include "./utils/test_utils.hpp"
#include <utility>
#include <vrm/pp/utils.hpp>

int main()
{
#define TEST_MACRO_GEN_LMBD(mReturn, mName, mBody) \
    auto mName = []() -> mReturn                   \
    {                                              \
        mBody                                      \
    };

    TEST_MACRO_GEN_LMBD(__R(std::pair<int, int>), __R(lambda1),
        __R(return std::make_pair(1, 5);));
    TEST_MACRO_GEN_LMBD(__R(std::pair<int, std::pair<float, float>>),
        __R(lambda2),
        __R(return std::make_pair(2, std::pair<float, float>(1.5f, 2.5f));));

    TEST_ASSERT(lambda1().first == 1);
    TEST_ASSERT(lambda1().second == 5);

    TEST_ASSERT(lambda2().first == 2);
    TEST_ASSERT(lambda2().second.first == 1.5f);
    TEST_ASSERT(lambda2().second.second == 2.5f);

#undef TEST_MACRO_GEN_LMBD

    return 0;
}