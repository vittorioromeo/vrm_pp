// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/arg_count.hpp>

#define VRM_PP_IMPL_CAT(...) \
    VRM_PP_TKNCAT_2(VRM_PP_IMPL_CAT_, VRM_PP_ARGCOUNT(__VA_ARGS__))(__VA_ARGS__)
#define VRM_PP_CAT(...) VRM_PP_IMPL_CAT(__VA_ARGS__)
