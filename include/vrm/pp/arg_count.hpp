// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>

#define VRM_PP_IMPL_N_ARG(...) VRM_PP_IMPL_NSEQ(__VA_ARGS__)

#define VRM_PP_IMPL_NARGS_COMMA(...) ,
#define VRM_PP_IMPL_NARGS_HASCOMMA(...) \
    VRM_PP_IMPL_N_ARG(__VA_ARGS__, VRM_PP_IMPL_CSEQ())

#define VRM_PP_IMPL_NARGS_DISPATCH_3_01(mN) 0
#define VRM_PP_IMPL_NARGS_DISPATCH_3_00(mN) 1
#define VRM_PP_IMPL_NARGS_DISPATCH_3_11(mN) mN

#define VRM_PP_IMPL_NARGS_DISPATCH_2(mA, mB, mN) \
    VRM_PP_IMPL_NARGS_DISPATCH_3_##mA##mB(mN)
#define VRM_PP_IMPL_NARGS_DISPATCH_1(mA, mB, mN) \
    VRM_PP_IMPL_NARGS_DISPATCH_2(mA, mB, mN)

#define VRM_PP_IMPL_ARGCOUNT(...)                                          \
    VRM_PP_IMPL_NARGS_DISPATCH_1(                                          \
        VRM_PP_IMPL_NARGS_HASCOMMA(__VA_ARGS__),                           \
        VRM_PP_IMPL_NARGS_HASCOMMA(VRM_PP_IMPL_NARGS_COMMA __VA_ARGS__()), \
        VRM_PP_IMPL_N_ARG(__VA_ARGS__, VRM_PP_IMPL_RSEQ()))

#define VRM_PP_ARGCOUNT(...) VRM_PP_IMPL_ARGCOUNT(__VA_ARGS__)
