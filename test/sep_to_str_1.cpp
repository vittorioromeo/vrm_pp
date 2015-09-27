#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/sep.hpp>
#include <vrm/pp/sep_to_str.hpp>

int main()
{
    using namespace std::literals;

    TEST_ASSERT_OP(VRM_PP_SEP_TOSTR(";", a, b, c), ==, "a;b;c"s);
    TEST_ASSERT_OP(VRM_PP_SEP_TOSTR(",", a, b, c), ==, "a,b,c"s);
    TEST_ASSERT_OP(VRM_PP_SEP_TOSTR(", ", a, b, c), ==, "a, b, c"s);

    std::string ss{";"}, s1{"a"}, s2{"b"}, s3{"c"};
    TEST_ASSERT_OP(VRM_PP_SEP(+, s1, s2, s3), ==, "abc");

    return 0;
}