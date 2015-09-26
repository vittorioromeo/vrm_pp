// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>

#define VRM_PP_IMPL_EVAL(...) VRM_PP_IMPL_EVAL_0(__VA_ARGS__)

/// @macro Forces a large number of preprocessor rescan passes.
#define VRM_PP_EVAL(...) VRM_PP_IMPL_EVAL(__VA_ARGS__)
