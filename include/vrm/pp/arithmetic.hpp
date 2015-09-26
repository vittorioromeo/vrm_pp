// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>

#define VRM_PP_IMPL_DECREMENT(mX) VRM_PP_IMPL_DECREMENT_##mX
#define VRM_PP_DECREMENT(mX) VRM_PP_IMPL_DECREMENT(mX)

#define VRM_PP_IMPL_INCREMENT(mX) VRM_PP_IMPL_INCREMENT_##mX
#define VRM_PP_INCREMENT(mX) VRM_PP_IMPL_INCREMENT(mX)
