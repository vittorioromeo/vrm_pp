// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace std::literals;

constexpr size_t argCount{128};
constexpr size_t arithCount{256};
constexpr size_t foreachCount{128};
constexpr size_t tplCount{64};
constexpr size_t repeatCount{128};
constexpr size_t evalDepth{4};

constexpr auto pfx("VRM_PP");

constexpr auto copyright(R"(// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com)");

std::string def_s("#define ");

std::ostringstream out;

void mkFill(size_t i)
{
    out << def_s + pfx + "_IMPL_TPL_FILL_" << i << "(m0)";

    if(i != 0)
        out << " "s + pfx + "_TPL_EXPLODE(m0),  ";
    else
        out << "             ";

    for(auto j(0u); j < tplCount - i - 1; ++j) out << "0, ";
    out << "0\n";
}

void mkFillReverse(size_t i)
{
    out << def_s + pfx + "_IMPL_TPL_FILL_REVERSE_" << i << "(m0)  ";

    for(auto j(0u); j < tplCount - i - 1; ++j) out << "0, ";
    out << "0";

    if(i != 0) out << ", "s + pfx + "_TPL_EXPLODE(m0)";

    out << "\n";
}

void mkTupleElem(size_t i)
{
    out << def_s + pfx + "_IMPL_TPL_ELEM_" << i << "(";

    for(auto j(0u); j < tplCount - 1; ++j) out << "m" << j << ", ";
    out << "m" << tplCount - 1 << ") m" << i << "\n";
}

void mkTupleElemReverse(size_t i)
{
    out << def_s + pfx + "_IMPL_TPL_ELEM_REVERSE_" << i << "(";

    for(auto j(0u); j < tplCount - 1; ++j) out << "m" << j << ", ";
    out << "m" << tplCount - 1 << ") m" << tplCount - i - 1 << "\n";
}

void mkCat(size_t i)
{
    out << def_s + pfx + "_IMPL_TPL_CAT_" << i << "(m0, m1, ...)  "s + pfx + "_IMPL_TPL_CAT_" << i - 1 << "("s + pfx + "_TPL_MAKE("s + pfx + "_TPL_EXPLODE(m0), "s + pfx + "_TPL_EXPLODE(m1)), __VA_ARGS__)\n";
}

void genTuple()
{
    for(auto i(0u); i < tplCount; ++i) mkFill(i);
    out << def_s + pfx + "_IMPL_TPL_FILL_" << tplCount << "(m0)   "s + pfx + "_TPL_EXPLODE(m0)\n";
    out << "\n";

    // tpl fill reverse
    for(auto i(0u); i < tplCount; ++i) mkFillReverse(i);
    out << def_s + pfx + "_IMPL_TPL_FILL_REVERSE_" << tplCount << "(m0)   "s + pfx + "_TPL_EXPLODE(m0)\n";
    out << "\n";

    // tpl elem
    for(auto i(0u); i < tplCount; ++i) mkTupleElem(i);
    out << "\n";

    // tpl elem reverse
    for(auto i(0u); i < tplCount; ++i) mkTupleElemReverse(i);
    out << "\n";

    // tpl cat
    out << def_s + pfx + "_IMPL_TPL_CAT_0()           "s + pfx + "_EMPTY()\n";
    out << def_s + pfx + "_IMPL_TPL_CAT_1(m0)         m0\n";
    out << def_s + pfx + "_IMPL_TPL_CAT_2(m0, m1)     "s + pfx + "_TPL_MAKE("s + pfx + "_TPL_EXPLODE(m0), "s + pfx + "_TPL_EXPLODE(m1))\n";
    for(auto i(3u); i < tplCount * 2 + 1; ++i) mkCat(i);
    out << "\n";

    out << def_s + pfx + "_TPL_MAX_SIZE " << tplCount << "\n";
    out << "\n";
}

void genArithmetic()
{
    // decrement
    out << def_s + pfx + "_IMPL_DECREMENT_0 0\n";
    out << def_s + pfx + "_IMPL_DECREMENT_1 0\n";
    out << def_s + pfx + "_IMPL_DECREMENT_2 1\n";
    for(auto i(3u); i < arithCount; ++i) out << def_s + pfx + "_IMPL_DECREMENT_" << i << " " << i - 1 << "\n";
    out << "\n";

    // increment
    for(auto i(0u); i < arithCount - 1; ++i) out << def_s + pfx + "_IMPL_INCREMENT_" << i << " " << i + 1 << "\n";
    out << def_s + pfx + "_IMPL_INCREMENT_" << arithCount - 1 << " " << arithCount << "\n";
    out << def_s + pfx + "_IMPL_INCREMENT_" << arithCount << " " << arithCount << "\n";
    out << "\n";

    // bool
    out << def_s + pfx + "_IMPL_BOOL_0 0\n";
    for(auto i(1u); i < arithCount; ++i) out << def_s + pfx + "_IMPL_BOOL_" << i << " 1\n";
    out << "\n";
}

void genArgCount()
{
    // nseq
    out << def_s + pfx + "_IMPL_NSEQ( ";
    for(auto i(0u); i < argCount - 1; ++i) out << "m" << i + 1 << ", ";
    out << "mN, ...) mN\n";
    out << "\n";

    // rseq
    out << def_s + pfx + "_IMPL_RSEQ()    ";
    for(auto i(argCount - 1); i > 0; --i) out << i << ", ";
    out << "0\n";

    // cseq
    out << def_s + pfx + "_IMPL_CSEQ()    ";
    for(auto i(argCount - 2); i > 0; --i) out << 1 << ", ";
    out << "0, 0\n";

    // cat
    out << def_s + pfx + "_IMPL_CAT_0()           "s + pfx + "_EMPTY()\n";
    out << def_s + pfx + "_IMPL_CAT_1(m0)         "s + pfx + "_EXPAND(m0)\n";
    out << def_s + pfx + "_IMPL_CAT_2(m0, m1)     "s + pfx + "_IMPL_CAT_1("s + pfx + "_TKNCAT_2(m0, m1))\n";
    for(auto i(3u); i < argCount; ++i) out << def_s + pfx + "_IMPL_CAT_" << i << "(m0, m1, ...)   "s + pfx + "_IMPL_CAT_" << i - 1 << "("s + pfx + "_TKNCAT_2(m0, m1), __VA_ARGS__)\n";
    out << "\n";
}

void genForeach()
{
    out << def_s + pfx + "_IMPL_FOREACH_0(mLast, mAction, mData)                  \n";
    out << def_s + pfx + "_IMPL_FOREACH_1(mLast, mAction, mData, mA0)             mAction(mLast, mData, mA0)\n";
    out << def_s + pfx + "_IMPL_FOREACH_2(mLast, mAction, mData, mA0, mA1)        mAction(mLast, mData, mA0) "s + pfx + "_IMPL_FOREACH_1("s + pfx + "_INCREMENT(mLast), mAction, mData, mA1)\n";

    for(auto i(2u); i < foreachCount; ++i)
    {
        out << def_s + pfx + "_IMPL_FOREACH_" << i + 1;
        out << "(mLast, mAction, mData, mA0, mA1, ...)       ";
        out << "mAction(mLast, mData, mA0) "s + pfx + "_IMPL_FOREACH_" << i << "("s + pfx + "_INCREMENT(mLast), mAction, mData, mA1, __VA_ARGS__)";
        out << "\n";
    }
}

void genForeachReverse()
{
    out << def_s + pfx + "_IMPL_FOREACH_REVERSE_0(mAction, mData)                     \n";
    out << def_s + pfx + "_IMPL_FOREACH_REVERSE_1(mAction, mData, mA0)                mAction(0, mData, mA0)\n";
    out << def_s + pfx + "_IMPL_FOREACH_REVERSE_2(mAction, mData, mA0, mA1)           mAction(1, mData, mA0) "s + pfx + "_IMPL_FOREACH_REVERSE_1(mAction, mData, mA1)\n";

    for(auto i(2u); i < foreachCount; ++i)
    {
        out << def_s + pfx + "_IMPL_FOREACH_REVERSE_" << i + 1;
        out << "(mAction, mData, mA0, mA1, ...)      ";
        out << "mAction(" << i << ", mData, mA0) "s + pfx + "_IMPL_FOREACH_REVERSE_" << i << "(mAction, mData, mA1, __VA_ARGS__)";
        out << "\n";
    }
}

void genRepeat()
{
    out << def_s + pfx + "_IMPL_REPEAT_DEC_0(mAction, mData)\n";

    for(auto i(0u); i < repeatCount; ++i)
        out << def_s + pfx + "_IMPL_REPEAT_DEC_" << i + 1 << "(mAction, mData) mAction(" << i << ", mData) "s + pfx + "_IMPL_REPEAT_DEC_" << i << "(mAction, mData)\n";

    out << "\n";

    out << def_s + pfx + "_IMPL_REPEAT_INC_0(mAction, mData, mLast)\n";

    for(auto i(0u); i < repeatCount; ++i)
        out << def_s + pfx + "_IMPL_REPEAT_INC_" << i + 1 << "(mAction, mData, mLast) mAction(mLast, mData) "s + pfx + "_IMPL_REPEAT_INC_" << i << "(mAction, mData, "s + pfx + "_INCREMENT(mLast))\n";
}

void genEval()
{
    out << def_s + pfx + "_IMPL_EVAL_" << evalDepth - 1 << "(...) __VA_ARGS__\n";

    for(auto i(1u); i < evalDepth; ++i)
    {
        auto dp(evalDepth - i);

        out << def_s + pfx + "_IMPL_EVAL_" << dp - 1 << "(...) ";

        for(auto j(0u); j < 3; ++j)
            out << ""s + pfx + "_IMPL_EVAL_" << dp << "(";

        out << "__VA_ARGS__";

        for(auto j(0u); j < 3; ++j)
            out << ")";

        out << "\n";
    }
}

int main()
{
    out << copyright << 
              "// (auto-generated file)\n\n"
              "#pragma once\n\n";

    genArithmetic();
    out << "\n\n";

    genArgCount();
    out << "\n\n";

    genTuple();
    out << "\n\n";

    genForeach();
    out << "\n\n";

    genForeachReverse();
    out << "\n\n";

    genRepeat();
    out << "\n";

    genEval();
    out << "\n";

    // out << "#endif";

    std::cout << out.str() << std::endl;

    return 0;
}