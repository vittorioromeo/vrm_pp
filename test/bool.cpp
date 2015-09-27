#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_BOOL(0) == 0);
    TEST_ASSERT(VRM_PP_BOOL(1) == 1);
    TEST_ASSERT(VRM_PP_BOOL(2) == 1);
    TEST_ASSERT(VRM_PP_BOOL(3) == 1);

    return 0;
}