#include "./utils/test_utils.hpp"
#include <vrm/pp/arithmetic.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_INCREMENT(1) == 2);
    TEST_ASSERT(VRM_PP_INCREMENT(100) == 101);
    TEST_ASSERT(VRM_PP_DECREMENT(1) == 0);
    TEST_ASSERT(VRM_PP_DECREMENT(100) == 99);

    return 0;
}