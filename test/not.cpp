#include "./utils/test_utils.hpp"
#include <vrm/pp/bool.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_NOT(35) == 0);
    TEST_ASSERT(VRM_PP_NOT(0) == 1);

    return 0;
}