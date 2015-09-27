#include "./utils/test_utils.hpp"
#include <vrm/pp/tpl.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_TPL_SIZE(VRM_PP_TPL_FILL(())) == VRM_PP_TPL_MAX_SIZE);
    TEST_ASSERT(VRM_PP_TPL_SIZE(VRM_PP_TPL_FILL((1))) == VRM_PP_TPL_MAX_SIZE);
    TEST_ASSERT(VRM_PP_TPL_SIZE(VRM_PP_TPL_FILL((1, 1))) ==
                VRM_PP_TPL_MAX_SIZE);
    TEST_ASSERT(VRM_PP_TPL_SIZE(VRM_PP_TPL_FILL((1, 1, 1))) ==
                VRM_PP_TPL_MAX_SIZE);

    return 0;
}