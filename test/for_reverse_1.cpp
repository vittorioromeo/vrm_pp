#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/for_each.hpp>
#include <vrm/pp/sep_to_str.hpp>
#include <vrm/pp/cat.hpp>

int main()
{
#define TEST_MACRO_ADDTEN(mX) VRM_PP_CAT(1, mX)
#define TEST_MACRO_FOREFFECT(mIdx, mData, mArg) \
    TEST_MACRO_ADDTEN(mArg) VRM_PP_COMMA_IF(mIdx)

    std::string s(VRM_PP_SEP_TOSTR(", ",
    VRM_PP_FOREACH_REVERSE(TEST_MACRO_FOREFFECT, VRM_PP_EMPTY(), 1, 2, 3, 4)));
    TEST_ASSERT_OP(s, ==, "11, 12, 13, 14");

#undef TEST_MACRO_ADDTEN
#undef TEST_MACRO_FOREFFECT

    return 0;
}