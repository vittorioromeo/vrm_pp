#include "./utils/test_utils.hpp"
#include <vrm/pp/arg_count.hpp>

int main()
{
    test_assert(VRM_PP_ARGCOUNT() == 0);
    test_assert(VRM_PP_ARGCOUNT(1) == 1);
    test_assert(VRM_PP_ARGCOUNT(1, 1) == 2);
    test_assert(VRM_PP_ARGCOUNT(1, 1, 1) == 3);
    test_assert(VRM_PP_ARGCOUNT(1, 1, 1, 1) == 4);
    test_assert(VRM_PP_ARGCOUNT(1, 1, 1, 1, 1) == 5);
    test_assert(VRM_PP_ARGCOUNT(1, 1, 1, 1, 1, 1) == 6);

    return 0;
}