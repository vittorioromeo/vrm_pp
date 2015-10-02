#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/sep_to_str.hpp>
#include <vrm/pp/tpl.hpp>
#include <vrm/pp/cat.hpp>

int main()
{
    using namespace std::literals;

#define CTS(...) VRM_PP_TOSTR(VRM_PP_CAT(__VA_ARGS__))

#define CTS_TE(...) CTS(VRM_PP_TPL_EXPLODE(VRM_PP_TPL_MAKE(__VA_ARGS__)))

#define TS_TE(...) \
    VRM_PP_TOSTR(VRM_PP_TPL_EXPLODE(VRM_PP_TPL_MAKE(__VA_ARGS__)))

    TEST_ASSERT(CTS() == ""s);
    TEST_ASSERT(CTS(a) == "a"s);
    TEST_ASSERT(CTS(a, b) == "ab"s);
    TEST_ASSERT(CTS(a, b, c) == "abc"s);

    TEST_ASSERT(CTS_TE() == ""s);
    TEST_ASSERT(CTS_TE(a) == "a"s);
    TEST_ASSERT(CTS_TE(a, b) == "ab"s);
    TEST_ASSERT(CTS_TE(a, b, c) == "abc"s);

    TEST_ASSERT(TS_TE() == ""s);
    TEST_ASSERT(TS_TE(a) == "a"s);
    TEST_ASSERT(TS_TE(a, b) == "a, b"s);
    TEST_ASSERT(TS_TE(a, b, c) == "a, b, c"s);

    return 0;
}