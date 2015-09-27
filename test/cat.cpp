#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/cat.hpp>

int main()
{
    TEST_ASSERT(std::string{VRM_PP_TOSTR(VRM_PP_CAT())} == "");
    TEST_ASSERT(VRM_PP_CAT(15) == 15);
    TEST_ASSERT(VRM_PP_CAT(15, 15) == 1515);
    TEST_ASSERT(VRM_PP_CAT(15, 15, 15) == 151515);

    return 0;
}