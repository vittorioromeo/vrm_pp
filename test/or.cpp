#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_OR(0, 0) == 0);
    TEST_ASSERT(VRM_PP_OR(0, 53) == 1);
    TEST_ASSERT(VRM_PP_OR(22, 0) == 1);
    TEST_ASSERT(VRM_PP_OR(35, 11) == 1);

    return 0;
}