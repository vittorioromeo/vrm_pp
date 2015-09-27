#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/repeat.hpp>

int main()
{
    using namespace std::literals;

#define TEST_MACRO_ACTION_REPEAT(mIdx, mData) VRM_PP_TOSTR(mIdx)

    auto sinc1 = VRM_PP_IMPL_REPEAT_INC(1, TEST_MACRO_ACTION_REPEAT, ());
    TEST_ASSERT_OP(sinc1, ==, "0"s);

    auto sdec1 = VRM_PP_IMPL_REPEAT_DEC(1, TEST_MACRO_ACTION_REPEAT, ());
    TEST_ASSERT_OP(sdec1, ==, "0"s);

    auto sinc5 = VRM_PP_IMPL_REPEAT_INC(5, TEST_MACRO_ACTION_REPEAT, ());
    TEST_ASSERT_OP(sinc5, ==, "01234"s);

    auto sdec5 = VRM_PP_IMPL_REPEAT_DEC(5, TEST_MACRO_ACTION_REPEAT, ());
    TEST_ASSERT_OP(sdec5, ==, "43210"s);

#undef TEST_MACRO_ACTION_REPEAT

    return 0;
}