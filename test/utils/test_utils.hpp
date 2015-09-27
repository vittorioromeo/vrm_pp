#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace impl
{
    template <typename T>
    inline void test_assert(bool x, const T& res, const char* expr)
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << expr << "\n"
              << "result: " << res << "\n";

        throw std::runtime_error{error.str()};
    }

    template <typename T>
    inline void test_assert_expected(bool x, const T& res, const char* expr,
                                     const char* expected)
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << expr << "\n"
              << "result: " << res << "\n"
              << "expected: " << expected << "\n";

        throw std::runtime_error{error.str()};
    }
}

#define TEST_ASSERT(expr)                     \
    do                                        \
    {                                         \
        impl::test_assert(expr, expr, #expr); \
    } while(false)

#define TEST_ASSERT_OP(lhs, op, rhs)                                      \
    do                                                                    \
    {                                                                     \
        impl::test_assert_expected(lhs op rhs, lhs, #lhs #op #rhs, #rhs); \
    } while(false)
