#pragma once

#include <exception>

inline void test_assert(bool x)
{
    if(!x)
    {
        std::terminate();
    }
}