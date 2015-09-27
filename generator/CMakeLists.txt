# Copyright (c) 2015-2016 Vittorio Romeo
# License: Academic Free License ("AFL") v. 3.0
# AFL License page: http://opensource.org/licenses/AFL-3.0
# http://vittorioromeo.info | vittorio.romeo@outlook.com

set(VRM_PP_GENERATOR_SRC "${VRM_PP_SOURCE_DIR}/generator/generator.cpp")
set(VRM_PP_GENERATED "${VRM_PP_SOURCE_DIR}/include/vrm/pp/generated/output.hpp")

# Compile the generator executable.
add_executable(generator "${VRM_PP_GENERATOR_SRC}")

# Add a custom target that will run the generator and output its result to a file.
add_custom_target(generator_run
    # The custom command target depends on the executable.
    DEPENDS generator

    # Redirect output to file.
    COMMAND generator > ${VRM_PP_GENERATED}
    COMMENT "run generated generator in ${VRM_PP_SOURCE_DIR}"
)