// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/bool.hpp>
#include <vrm/pp/for_each.hpp>

#define VRM_PP_IMPL_SEP_TOSTR(mIdx, mData, mArg) \
    VRM_PP_TOSTR(mArg) VRM_PP_IF(mIdx, mData, VRM_PP_EMPTY())
#define VRM_PP_SEP_TOSTR(mSeparator, ...) \
    VRM_PP_FOREACH_REVERSE(VRM_PP_IMPL_SEP_TOSTR, mSeparator, __VA_ARGS__)
