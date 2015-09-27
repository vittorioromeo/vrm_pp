# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# Basic project setup.
cmake_minimum_required(VERSION 3.0)
project(vrm_pp CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()

# Alias the source directory.
set(VRM_PP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Setup user options.
option(VRM_PP_ENABLE_WERROR   "Fail and stop if a warning is triggered." OFF)
option(VRM_PP_ENABLE_MEMCHECK "Run the unit tests and examples under Valgrind if it is found." OFF)
option(VRM_PP_ENABLE_EXCEPTIONS "Build with exceptions enabled." ON)

# Setup compiler flags.
include(CheckCXXCompilerFlag)

# Macro: creates `testname` variable that checks for compiler flag `flag`.
# The flag is enabled, if possible.
macro(vrm_pp_append_flag testname flag)
    check_cxx_compiler_flag(${flag} ${testname})
    if (${testname})
        add_compile_options(${flag})
    endif()
endmacro()

# Enable `-Werror` if the user wants to.
if (VRM_PP_ENABLE_WERROR)
    vrm_pp_append_flag(VRM_PP_HAS_WERROR -Werror)
    vrm_pp_append_flag(VRM_PP_HAS_WX -WX)
endif()

# Disable exceptions if the user wants to.
if (NOT VRM_PP_ENABLE_EXCEPTIONS)
    vrm_pp_append_flag(VRM_PP_HAS_FNO_EXCEPTIONS -fno-exceptions)
endif()

# Other compiler flags.
vrm_pp_append_flag(VRM_PP_HAS_PEDANTIC                          -pedantic)
vrm_pp_append_flag(VRM_PP_HAS_STDCXX1Y                          -std=c++1y)
vrm_pp_append_flag(VRM_PP_HAS_W                                 -W)
vrm_pp_append_flag(VRM_PP_HAS_WALL                              -Wall)
vrm_pp_append_flag(VRM_PP_HAS_WEXTRA                            -Wextra)
vrm_pp_append_flag(VRM_PP_HAS_WNO_UNUSED_LOCAL_TYPEDEFS         -Wno-unused-local-typedefs)
vrm_pp_append_flag(VRM_PP_HAS_WWRITE_STRINGS                    -Wwrite-strings)
vrm_pp_append_flag(VRM_PP_HAS_WSHADOW                           -Wshadow)
vrm_pp_append_flag(VRM_PP_HAS_WUNDEF                            -Wundef)
vrm_pp_append_flag(VRM_PP_HAS_WNO_MISSING_FIELD_INITIALIZERS    -Wno-missing-field-initializers)
vrm_pp_append_flag(VRM_PP_HAS_WPOINTER_ARITH                    -Wpointer-arith)
vrm_pp_append_flag(VRM_PP_HAS_WCAST_ALIGN                       -Wcast-align)
vrm_pp_append_flag(VRM_PP_HAS_WNO_UNREACHABLE_CODE              -Wno-unreachable-code)
vrm_pp_append_flag(VRM_PP_HAS_WNON_VIRTUAL_DTOR                 -Wnon-virtual-dtor)
vrm_pp_append_flag(VRM_PP_HAS_WOVERLOADED_VIRTUAL               -Woverloaded-virtual)

# Look for valgrind, if memcheck is enabled.
if (VRM_PP_ENABLE_MEMCHECK)
    find_package(Valgrind REQUIRED)
endif()


# Return an unique name for a file target.
# Replaces slashes with `.`, assumes `.cpp` if the extension is not specified.
function(vrm_pp_target_name_for out file)
    if (NOT ARGV2)
        set(_extension ".cpp")
    else()
        set(_extension "${ARGV2}")
    endif()

    file(RELATIVE_PATH _relative ${VRM_PP_SOURCE_DIR} ${file})
    string(REPLACE "${_extension}" "" _name ${_relative})
    string(REGEX REPLACE "/" "." _name ${_name})
    set(${out} "${_name}" PARENT_SCOPE)
endfunction()

# `vrm_pp_add_test(<name> <command> [<arg>...])`
# Creates a test called `name` which runs the given `command` with the given `arg`uments. 
# Uses valgrind if enabled.
function(vrm_pp_add_test name)
    if (VRM_PP_ENABLE_MEMCHECK)
        add_test(${name} ${Valgrind_EXECUTABLE} --leak-check=full --error-exitcode=1 ${ARGN})
    else()
        add_test(${name} ${ARGN})
    endif()
endfunction()

# `vrm_pp_list_remove_glob(<list> <GLOB|GLOB_RECURSE> [globbing expressions]...)`
# Returns a list of globbed objects except the listed ones.
macro(vrm_pp_list_remove_glob list glob)
    list(REMOVE_ITEM ${list} ${ARGN})
endmacro()

# The `check` target runs all tests and examples.
add_custom_target(check ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Build and then run all the tests and examples.")

# Setup subdirectories.
add_subdirectory(generator)
add_subdirectory(test)

# Tests depend on generator.
add_dependencies(tests generator_run)