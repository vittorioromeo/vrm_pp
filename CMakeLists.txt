# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup project
##############################################################################
cmake_minimum_required(VERSION 3.0)
project(vrm_pp CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()

set(VRM_PP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

##############################################################################
# Setup CMake options
##############################################################################
option(VRM_PP_ENABLE_WERROR   "Fail and stop if a warning is triggered." OFF)
option(VRM_PP_ENABLE_MEMCHECK "Run the unit tests and examples under Valgrind if it is found." OFF)
# option(VRM_PP_ENABLE_CONCEPT_CHECKS "Enable concept checking in the interface methods." ON)

# option(VRM_PP_ENABLE_STRING_UDL
# "Enable the GNU extension allowing the special string literal operator\
#  template, which enables the _s suffix for creating compile-time strings." ON)

option(VRM_PP_ENABLE_EXCEPTIONS
"Build with exceptions enabled. Note that Hana does not make use of exceptions,\
 but this switch can be disabled when building the tests to assess that it is\
 really the case." ON)


##############################################################################
# Setup compiler flags (more can be set on a per-target basis or in subdirectories)
##############################################################################
include(CheckCXXCompilerFlag)
macro(vrm_pp_append_flag testname flag)
    check_cxx_compiler_flag(${flag} ${testname})
    if (${testname})
        add_compile_options(${flag})
    endif()
endmacro()

# Compiler flags controlled by CMake options above
if (VRM_PP_ENABLE_WERROR)
    vrm_pp_append_flag(VRM_PP_HAS_WERROR -Werror)
    vrm_pp_append_flag(VRM_PP_HAS_WX -WX)
endif()

if (NOT VRM_PP_ENABLE_EXCEPTIONS)
    vrm_pp_append_flag(VRM_PP_HAS_FNO_EXCEPTIONS -fno-exceptions)
endif()

# Other compiler flags
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

##############################################################################
# Search for packages.
#
# Behavior when the package is found or not is customized at the
# point where the package is required.
##############################################################################
# find_package(Boost)
# find_package(Doxygen)
# find_package(Git)
# find_package(Meta)
# find_package(MPL11)
# find_package(PythonInterp 2.7)
# find_package(Ruby 2.1)

if (VRM_PP_ENABLE_MEMCHECK)
    find_package(Valgrind REQUIRED)
endif()


##############################################################################
# Setup custom functions to ease the creation of targets
##############################################################################
#   vrm_pp_target_name_for(<output variable> <source file> [ext])
#
# Return the target name associated to a source file. If the path of the
# source file relative from the root of Hana is `path/to/source/file.ext`,
# the target name associated to it will be `path.to.source.file`.
#
# The extension of the file should be specified as a last argument. If no
# extension is specified, the `.cpp` extension is assumed.
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

#   vrm_pp_add_test(<name> <command> [<arg>...])
#
# Creates a test called `name`, which runs the given `command` with the given
# `arg`uments. However, if `VRM_PP_ENABLE_MEMCHECK` is set to `ON`, the
# test will run the provided command under the memory checker.
function(vrm_pp_add_test name)
    if (VRM_PP_ENABLE_MEMCHECK)
        add_test(${name} ${Valgrind_EXECUTABLE} --leak-check=full --error-exitcode=1 ${ARGN})
    else()
        add_test(${name} ${ARGN})
    endif()
endfunction()

#   vrm_pp_list_remove_glob(<list> <GLOB|GLOB_RECURSE> [globbing expressions]...)
#
# Generates a list of files matching the given glob expressions, and remove
# the matched elements from the given <list>.
macro(vrm_pp_list_remove_glob list glob)
    
    list(REMOVE_ITEM ${list} ${ARGN})
endmacro()


##############################################################################
# Setup the `check` target to build and then run all the tests and examples.
##############################################################################
add_custom_target(check ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Build and then run all the tests and examples.")

##############################################################################
# Setup subdirectories
##############################################################################
add_subdirectory(test)