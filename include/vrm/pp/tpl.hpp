// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/arg_count.hpp>

#define VRM_PP_IMPL_TPL_EXPLODE(...) __VA_ARGS__
#define VRM_PP_IMPL_TPL_MAKE(...) (__VA_ARGS__)

#define VRM_PP_TPL_EXPLODE(mTpl) VRM_PP_DEFER(VRM_PP_IMPL_TPL_EXPLODE mTpl)
#define VRM_PP_TPL_MAKE(...) VRM_PP_IMPL_TPL_MAKE(__VA_ARGS__)

#define VRM_PP_TPL_FILL_IMPL(mTpl) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_TPL_FILL_, VRM_PP_TPL_SIZE(mTpl))(mTpl)
#define VRM_PP_TPL_FILL_REVERSE_IMPL(mTpl) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_TPL_FILL_REVERSE_, VRM_PP_TPL_SIZE(mTpl))(mTpl)
#define VRM_PP_IMPL_TPL_ELEM(mTpl, mIdx)         \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_TPL_ELEM_, mIdx) \
    VRM_PP_DEFER(VRM_PP_TPL_FILL(mTpl))
#define VRM_PP_IMPL_TPL_ELEM_REVERSE(mTpl, mIdx)         \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_TPL_ELEM_REVERSE_, mIdx) \
    VRM_PP_DEFER(VRM_PP_TPL_FILL_REVERSE(mTpl))
#define VRM_PP_IMPL_TPL_CAT(...) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_TPL_CAT_, \
                    VRM_PP_ARGCOUNT(__VA_ARGS__))(__VA_ARGS__)
#define VRM_PP_IMPL_TPL_SIZE(mTpl) VRM_PP_ARGCOUNT(VRM_PP_TPL_EXPLODE(mTpl))
#define VRM_PP_IMPL_TPL_HEAD(mTpl) VRM_PP_DEFER(VRM_PP_TPL_ELEM(mTpl, 0))
#define VRM_PP_IMPL_TPL_TAIL(mTpl) \
    VRM_PP_DEFER(VRM_PP_TPL_ELEM_REVERSE(mTpl, 0))
#define VRM_PP_IMPL_TPL_PUSH_BACK(mTpl, mArg) \
    VRM_PP_DEFER(VRM_PP_TPL_MAKE(VRM_PP_TPL_EXPLODE(mTpl), mArg))
#define VRM_PP_IMPL_TPL_PUSH_FRONT(mTpl, mArg) \
    VRM_PP_DEFER(VRM_PP_TPL_MAKE(mArg, VRM_PP_TPL_EXPLODE(mTpl)))

#define VRM_PP_TPL_FILL(mTpl) (VRM_PP_TPL_FILL_IMPL(mTpl))
#define VRM_PP_TPL_FILL_REVERSE(mTpl) (VRM_PP_TPL_FILL_REVERSE_IMPL(mTpl))
#define VRM_PP_TPL_ELEM(mTpl, mIdx) \
    VRM_PP_DEFER(VRM_PP_IMPL_TPL_ELEM(mTpl, mIdx))
#define VRM_PP_TPL_ELEM_REVERSE(mTpl, mIdx) \
    VRM_PP_DEFER(VRM_PP_IMPL_TPL_ELEM_REVERSE(mTpl, mIdx))
#define VRM_PP_TPL_CAT(...) VRM_PP_IMPL_TPL_CAT(__VA_ARGS__)
#define VRM_PP_TPL_SIZE(mTpl) VRM_PP_IMPL_TPL_SIZE(mTpl)
#define VRM_PP_TPL_HEAD(mTpl) VRM_PP_IMPL_TPL_HEAD(mTpl)
#define VRM_PP_TPL_TAIL(mTpl) VRM_PP_IMPL_TPL_TAIL(mTpl)
#define VRM_PP_TPL_PUSH_BACK(mTpl, mArg) VRM_PP_IMPL_TPL_PUSH_BACK(mTpl, mArg)
#define VRM_PP_TPL_PUSH_FRONT(mTpl, mArg) VRM_PP_IMPL_TPL_PUSH_FRONT(mTpl, mArg)
