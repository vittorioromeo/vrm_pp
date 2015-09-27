#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_IF(VRM_PP_XOR(35, 11), 10, 20) == 20);
    TEST_ASSERT(VRM_PP_IF(1, 10, 20) == 10);

    return 0;
}