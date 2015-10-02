#include "./utils/test_utils.hpp"
#include <vrm/pp/tpl.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_TPL_HEAD((1, 2, 3)) == 1);
    TEST_ASSERT(VRM_PP_TPL_TAIL((1, 2, 3)) == 3);

    TEST_ASSERT(VRM_PP_TPL_HEAD((1, 2)) == 1);
    TEST_ASSERT(VRM_PP_TPL_TAIL((1, 2)) == 2);

    TEST_ASSERT(VRM_PP_TPL_HEAD((1)) == 1);
    TEST_ASSERT(VRM_PP_TPL_TAIL((1)) == 1);

    return 0;
}