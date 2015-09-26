// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>

#define VRM_PP_IMPL_BOOL(mX) VRM_PP_IMPL_BOOL_##mX
#define VRM_PP_BOOL(mX) VRM_PP_IMPL_BOOL(mX)

#define VRM_PP_IMPL_BITNOT_0 1
#define VRM_PP_IMPL_BITNOT_1 0

#define VRM_PP_IMPL_BITAND_00 0
#define VRM_PP_IMPL_BITAND_01 0
#define VRM_PP_IMPL_BITAND_10 0
#define VRM_PP_IMPL_BITAND_11 1

#define VRM_PP_IMPL_BITOR_00 0
#define VRM_PP_IMPL_BITOR_01 1
#define VRM_PP_IMPL_BITOR_10 1
#define VRM_PP_IMPL_BITOR_11 1

#define VRM_PP_IMPL_BITNOR_00 1
#define VRM_PP_IMPL_BITNOR_01 0
#define VRM_PP_IMPL_BITNOR_10 0
#define VRM_PP_IMPL_BITNOR_11 0

#define VRM_PP_IMPL_BITXOR_00 0
#define VRM_PP_IMPL_BITXOR_01 1
#define VRM_PP_IMPL_BITXOR_10 1
#define VRM_PP_IMPL_BITXOR_11 0

#define VRM_PP_BITNOT(mX) VRM_PP_TKNCAT_2(VRM_PP_IMPL_BITNOT_, VRM_PP_DEFER(mX))
#define VRM_PP_BITAND(m0, m1) \
    VRM_PP_TKNCAT_3(VRM_PP_IMPL_BITAND_, VRM_PP_DEFER(m0), VRM_PP_DEFER(m1))
#define VRM_PP_BITOR(m0, m1) \
    VRM_PP_TKNCAT_3(VRM_PP_IMPL_BITOR_, VRM_PP_DEFER(m0), VRM_PP_DEFER(m1))
#define VRM_PP_BITNOR(m0, m1) \
    VRM_PP_TKNCAT_3(VRM_PP_IMPL_BITNOR_, VRM_PP_DEFER(m0), VRM_PP_DEFER(m1))
#define VRM_PP_BITXOR(m0, m1) \
    VRM_PP_TKNCAT_3(VRM_PP_IMPL_BITXOR_, VRM_PP_DEFER(m0), VRM_PP_DEFER(m1))

#define VRM_PP_IMPL_NOT(mX) VRM_PP_BITNOT(VRM_PP_BOOL(mX))
#define VRM_PP_IMPL_AND(m0, m1) VRM_PP_BITAND(VRM_PP_BOOL(m0), VRM_PP_BOOL(m1))
#define VRM_PP_IMPL_OR(m0, m1) VRM_PP_BITOR(VRM_PP_BOOL(m0), VRM_PP_BOOL(m1))
#define VRM_PP_IMPL_NOR(m0, m1) VRM_PP_BITNOR(VRM_PP_BOOL(m0), VRM_PP_BOOL(m1))
#define VRM_PP_IMPL_XOR(m0, m1) VRM_PP_BITXOR(VRM_PP_BOOL(m0), VRM_PP_BOOL(m1))

#define VRM_PP_NOT(mX) VRM_PP_IMPL_NOT(mX)
#define VRM_PP_AND(m0, m1) VRM_PP_IMPL_AND(m0, m1)
#define VRM_PP_OR(m0, m1) VRM_PP_IMPL_OR(m0, m1)
#define VRM_PP_NOR(m0, m1) VRM_PP_IMPL_NOR(m0, m1)
#define VRM_PP_XOR(m0, m1) VRM_PP_IMPL_XOR(m0, m1)

#define VRM_PP_IMPL_IF_0(mTrue, mFalse) mFalse
#define VRM_PP_IMPL_IF_1(mTrue, mFalse) mTrue
#define VRM_PP_IF(mCond, mTrue, mFalse) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_IF_, VRM_PP_BOOL(mCond))(mTrue, mFalse)

#define VRM_PP_COMMA_IF(mCond) VRM_PP_IF(mCond, VRM_PP_COMMA, VRM_PP_EMPTY)()
