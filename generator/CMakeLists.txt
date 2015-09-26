# Copyright (c) 2015-2016 Vittorio Romeo
# License: Academic Free License ("AFL") v. 3.0
# AFL License page: http://opensource.org/licenses/AFL-3.0
# http://vittorioromeo.info | vittorio.romeo@outlook.com

add_executable(generator "${VRM_PP_SOURCE_DIR}/generator/generator.cpp")
set(VRM_PP_GENERATED "${VRM_PP_SOURCE_DIR}/include/vrm/pp/generated/output.hpp")

add_custom_target(generator_run
  DEPENDS generator
  COMMAND generator > ${VRM_PP_GENERATED}
  WORKING_DIRECTORY ${VRM_PP_SOURCE_DIR}
  COMMENT "run generated generator in ${VRM_PP_SOURCE_DIR}"
)

add_dependencies(generator_run generator)