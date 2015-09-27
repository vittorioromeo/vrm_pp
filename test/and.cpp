#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_AND(0, 0) == 0);
    TEST_ASSERT(VRM_PP_AND(0, 53) == 0);
    TEST_ASSERT(VRM_PP_AND(22, 0) == 0);
    TEST_ASSERT(VRM_PP_AND(35, 11) == 1);

    return 0;
}