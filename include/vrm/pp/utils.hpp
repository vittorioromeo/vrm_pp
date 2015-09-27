// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/generated.hpp>

#define VRM_PP_EMPTY()
#define VRM_PP_DOT() .
#define VRM_PP_COMMA() ,
#define VRM_PP_DEFER(mX) mX VRM_PP_EMPTY()
#define VRM_PP_OBSTRUCT(...) __VA_ARGS__ VRM_PP_DEFER(VRM_PP_EMPTY)()
#define VRM_PP_EXPAND(...) __VA_ARGS__
#define VRM_PP_EAT(...)

#define VRM_PP_RAW(...) __VA_ARGS__
#define __R(...) VRM_PP_RAW(__VA_ARGS__)

#define VRM_PP_TOSTR_IMPL(...) #__VA_ARGS__
#define VRM_PP_TOSTR(...) VRM_PP_TOSTR_IMPL(__VA_ARGS__)

#define VRM_PP_IMPL_TKNCAT_2(m0, m1) m0##m1
#define VRM_PP_IMPL_TKNCAT_3(m0, m1, m2) m0##m1##m2
#define VRM_PP_IMPL_TKNCAT_4(m0, m1, m2, m3) m0##m1##m2##m3
#define VRM_PP_IMPL_TKNCAT_5(m0, m1, m2, m3, m4) m0##m1##m2##m3##m4

#define VRM_PP_TKNCAT_2(m0, m1) VRM_PP_IMPL_TKNCAT_2(m0, m1)
#define VRM_PP_TKNCAT_3(m0, m1, m2) VRM_PP_IMPL_TKNCAT_3(m0, m1, m2)
#define VRM_PP_TKNCAT_4(m0, m1, m2, m3) VRM_PP_IMPL_TKNCAT_4(m0, m1, m2, m3)
#define VRM_PP_TKNCAT_5(m0, m1, m2, m3, m4) \
    VRM_PP_IMPL_TKNCAT_5(m0, m1, m2, m3, m4)
