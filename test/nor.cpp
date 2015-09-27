#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_NOR(0, 0) == 1);
    TEST_ASSERT(VRM_PP_NOR(0, 53) == 0);
    TEST_ASSERT(VRM_PP_NOR(22, 0) == 0);
    TEST_ASSERT(VRM_PP_NOR(35, 11) == 0);

    return 0;
}