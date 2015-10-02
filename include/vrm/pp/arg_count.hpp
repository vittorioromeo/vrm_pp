// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>

#define VRM_PP_IMPL_N_ARG(...) VRM_PP_IMPL_NSEQ(__VA_ARGS__)

#define VRM_PP_IMPL_ARGCOUNT(...) \
    VRM_PP_IMPL_N_ARG(__VA_ARGS__, VRM_PP_IMPL_RSEQ())

#define VRM_PP_ARGCOUNT(...) VRM_PP_IMPL_ARGCOUNT(__VA_ARGS__)
