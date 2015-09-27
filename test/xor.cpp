#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_XOR(0, 0) == 0);
    TEST_ASSERT(VRM_PP_XOR(0, 53) == 1);
    TEST_ASSERT(VRM_PP_XOR(22, 0) == 1);
    TEST_ASSERT(VRM_PP_XOR(35, 11) == 0);

    return 0;
}