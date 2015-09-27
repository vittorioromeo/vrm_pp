// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/arithmetic.hpp>

#define VRM_PP_IMPL_REPEAT_DEC(mTimes, mAction, mData) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_REPEAT_DEC_, mTimes)(mAction, mData)
#define VRM_PP_REPEAT_DEC(...) VRM_PP_IMPL_REPEAT_DEC(__VA_ARGS__)

#define VRM_PP_IMPL_REPEAT_INC(mTimes, mAction, mData) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_REPEAT_INC_, mTimes)(mAction, mData, 0)
#define VRM_PP_REPEAT_INC(...) VRM_PP_IMPL_REPEAT_INC(__VA_ARGS__)
