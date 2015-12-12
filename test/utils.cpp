#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/utils.hpp>
#include <vrm/pp/eval.hpp>
#include <vrm/pp/bool.hpp>
#include <vrm/pp/arithmetic.hpp>

int main()
{
#define TEMP_TEST_TEN 10
#define TEMP_TEST_TEN_TX() 10

    TEST_ASSERT_OP(10, ==, 10);
    TEST_ASSERT_OP(10, ==, VRM_PP_DEFER(10));
    TEST_ASSERT_OP(10, ==, VRM_PP_OBSTRUCT(10));

    TEST_ASSERT_OP(10, ==, TEMP_TEST_TEN);
    TEST_ASSERT_OP(10, ==, VRM_PP_DEFER(TEMP_TEST_TEN));
    TEST_ASSERT_OP(10, ==, VRM_PP_OBSTRUCT(TEMP_TEST_TEN));

    TEST_ASSERT_OP(TEMP_TEST_TEN, ==, TEMP_TEST_TEN);
    TEST_ASSERT_OP(TEMP_TEST_TEN, ==, VRM_PP_DEFER(TEMP_TEST_TEN));
    TEST_ASSERT_OP(TEMP_TEST_TEN, ==, VRM_PP_OBSTRUCT(TEMP_TEST_TEN));

    TEST_ASSERT_OP(TEMP_TEST_TEN_TX(), ==, 10);

    // Does not compile, as expected:
    //  {
    //      auto i = VRM_PP_DEFER(TEMP_TEST_TEN_TX)();
    //      TEST_ASSERT_OP(i, ==, 10);
    //  }

    // Does not compile, as expected:
    //  {
    //      auto i = VRM_PP_OBSTRUCT(TEMP_TEST_TEN_TX)();
    //      TEST_ASSERT_OP(i, ==, 10);
    //  }

    {
        auto i = VRM_PP_DEFER(VRM_PP_DEFER(TEMP_TEST_TEN_TX)());
        TEST_ASSERT_OP(i, ==, 10);
    }

    {
        auto i =
            VRM_PP_EXPAND(VRM_PP_EXPAND(VRM_PP_OBSTRUCT(TEMP_TEST_TEN_TX)()));
        TEST_ASSERT_OP(i, ==, 10);
    }

    {
        auto i = VRM_PP_EVAL(VRM_PP_DEFER(TEMP_TEST_TEN_TX)());
        TEST_ASSERT_OP(i, ==, 10);
    }

    {
        auto i =
            VRM_PP_EVAL(VRM_PP_EXPAND(VRM_PP_OBSTRUCT(TEMP_TEST_TEN_TX)()));
        TEST_ASSERT_OP(i, ==, 10);
    }

    {
        auto i = VRM_PP_EVAL(VRM_PP_OBSTRUCT(TEMP_TEST_TEN_TX)());
        TEST_ASSERT_OP(i, ==, 10);
    }

#undef TEMP_TEST_TEN
#undef TEMP_TEST_TEN_TX

#define WHEN(c) VRM_PP_IF(c, VRM_PP_EXPAND, VRM_PP_EAT)

/*
    #define WHILE_INDIRECT() WHILE
    #define WHILE(pred, op, ...) \
        WHEN(pred(__VA_ARGS__))  \
        (VRM_PP_DEFER(WHILE_INDIRECT)()(pred, op, op(__VA_ARGS__)), __VA_ARGS__)
*/

#define REPEAT_INDIRECT() REPEAT
#define REPEAT(count, macro, ...)                                       \
    WHEN(count)                                                         \
    (VRM_PP_OBSTRUCT(REPEAT_INDIRECT)()(VRM_PP_DECREMENT(count), macro, \
        __VA_ARGS__)VRM_PP_OBSTRUCT(macro)(VRM_PP_DECREMENT(count),     \
        __VA_ARGS__))

#define TEMP_TEST_M(i, _) i

    auto x = VRM_PP_TOSTR(VRM_PP_EVAL(REPEAT(8, TEMP_TEST_M, ~)));
    TEST_ASSERT_OP(x, ==, std::string{"01234567"});

#undef TEMP_TEST_M
#undef REPEAT
#undef REPEAT_INDIRECT
// #undef WHILE
// #undef WHILE_INDIRECT
#undef WHEN

    return 0;
}
