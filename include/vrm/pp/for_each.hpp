// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/arg_count.hpp>
#include <vrm/pp/arithmetic.hpp>

#define VRM_PP_IMPL_FOREACH(mAction, mData, ...) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_FOREACH_, VRM_PP_ARGCOUNT(__VA_ARGS__))( \
        0, mAction, mData, __VA_ARGS__)
#define VRM_PP_FOREACH(...) VRM_PP_IMPL_FOREACH(__VA_ARGS__)

#define VRM_PP_IMPL_FOREACH_REVERSE(mAction, mData, ...) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_FOREACH_REVERSE_,        \
                    VRM_PP_ARGCOUNT(__VA_ARGS__))(mAction, mData, __VA_ARGS__)
#define VRM_PP_FOREACH_REVERSE(...) VRM_PP_IMPL_FOREACH_REVERSE(__VA_ARGS__)
