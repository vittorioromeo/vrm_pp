#include "./utils/test_utils.hpp"
#include <vrm/pp/tpl.hpp>

int main()
{
    TEST_ASSERT(VRM_PP_TPL_ELEM(VRM_PP_TPL_PUSH_FRONT((1, 2), 3), 0) == 3);
    TEST_ASSERT(VRM_PP_TPL_ELEM(VRM_PP_TPL_PUSH_FRONT((1, 2), 3), 2) == 2);

    TEST_ASSERT(VRM_PP_TPL_ELEM(VRM_PP_TPL_PUSH_BACK((1, 2), 3), 0) == 1);
    TEST_ASSERT(VRM_PP_TPL_ELEM(VRM_PP_TPL_PUSH_BACK((1, 2), 3), 2) == 3);

    return 0;
}