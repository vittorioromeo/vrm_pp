#include "./utils/test_utils.hpp"
#include <vrm/pp/arg_count.hpp>

int main()
{
    // TEST_ASSERT(VRM_PP_ARGCOUNT() == 0);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1) == 1);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1, 1) == 2);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1, 1, 1) == 3);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1, 1, 1, 1) == 4);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1, 1, 1, 1, 1) == 5);
    TEST_ASSERT(VRM_PP_ARGCOUNT(1, 1, 1, 1, 1, 1) == 6);

    // TEST_ASSERT(VRM_PP_ARGCOUNT() == 0);
    TEST_ASSERT(VRM_PP_ARGCOUNT(()) == 1);
    TEST_ASSERT(VRM_PP_ARGCOUNT((), ()) == 2);
    TEST_ASSERT(VRM_PP_ARGCOUNT((), (), ()) == 3);
    TEST_ASSERT(VRM_PP_ARGCOUNT((), (), (), ()) == 4);
    TEST_ASSERT(VRM_PP_ARGCOUNT((), (), (), (), ()) == 5);
    TEST_ASSERT(VRM_PP_ARGCOUNT((), (), (), (), (), ()) == 6);

    return 0;
}