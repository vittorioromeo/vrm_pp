# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# TODO:
macro(vrm_cmake_init_project project_name)
    cmake_minimum_required(VERSION 3.0)
    project(${project_name} CXX)
    vrm_cmake_init_project_name_upper()
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endmacro()

# TODO:
macro(vrm_cmake_init_project_name_upper)
    string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
endmacro()

# TODO:
macro(vrm_cmake_project_prefix x)
    # TODO: ??
    return("${PROJECT_NAME_UPPER}_${x}")
endmacro()


# TODO:
macro(vrm_cmake_set_source_dir)
    set("${PROJECT_NAME_UPPER}_SOURCE_DIR" "${CMAKE_CURRENT_SOURCE_DIR}")
endmacro()

# Sets CMake minimum required version, project name, default CMake module path,
# and project-specific source dir variable.
macro(vrm_cmake_basic_setup project_name)
    vrm_cmake_init_project(${project_name})
    vrm_cmake_set_source_dir()
endmacro()

# TODO:
macro(vrm_cmake_project_option name desc default)
    option("{PROJECT_NAME_UPPER}_${name}" desc default)
endmacro()

# TODO:
macro(vrm_cmake_init_compiler_flag_check)

    # TODO:
    # if("${VRM_CMAKE_COMPILER_FLAG_CHECK_INCLUDED}")
        set(VRM_CMAKE_COMPILER_FLAG_CHECK_INCLUDED TRUE)
        include(CheckCXXCompilerFlag)
    #endif()
endmacro()

# Macro: creates `testname` variable that checks for compiler flag `flag`.
# The flag is enabled, if possible.
macro(vrm_cmake_add_compiler_flag testname flag)
    set(PROJECT_TESTNAME "${PROJECT_NAME_UPPER}_${testname}")

    vrm_cmake_init_compiler_flag_check()
    check_cxx_compiler_flag(${flag} ${PROJECT_TESTNAME})
    
    if (${PROJECT_TESTNAME})
        add_compile_options(${flag})
    endif()
endmacro()

# TODO:
macro(vrm_cmake_header_only_install file_list src_dir dest_dir)
    set_source_files_properties(${file_list} PROPERTIES HEADER_FILE_ONLY 1)
    add_library(HEADER_ONLY_TARGET STATIC ${file_list})
    set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)
    install(DIRECTORY ${src_dir} DESTINATION ${dest_dir})
endmacro()

# TODO:
macro(vrm_cmake_header_only_install_glob src_dir dest_dir)
    # Glob library header files.
    file(GLOB_RECURSE INSTALL_FILES_LIST "${src_dir}")

    # Create header-only install target
    vrm_cmake_header_only_install("${INSTALL_FILES_LIST}" "${src_dir}" "${dest_dir}")
endmacro()

# TODO:
macro(vrm_check_target)
    add_custom_target(check 
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Build and then run all the tests and examples.")
endmacro()




# Basic project setup.
vrm_cmake_basic_setup(vrm_pp)
enable_testing()

# Alias the source directory.
set(VRM_PP_INC_DIR "${VRM_PP_SOURCE_DIR}/include/")

# Setup user options.
vrm_cmake_project_option(ENABLE_WERROR "Fail and stop if a warning is triggered." OFF)
vrm_cmake_project_option(ENABLE_MEMCHECK "Run the unit tests and examples under Valgrind if it is found." OFF)
vrm_cmake_project_option(ENABLE_EXCEPTIONS "Build with exceptions enabled." ON)

# Setup compiler flags.
vrm_cmake_init_compiler_flag_check()

# Enable `-Werror` if the user wants to.
if (VRM_PP_ENABLE_WERROR)
    vrm_cmake_add_compiler_flag(HAS_WERROR -Werror)
    vrm_cmake_add_compiler_flag(HAS_WX -WX)
endif()

# Disable exceptions if the user wants to.
if (NOT VRM_PP_ENABLE_EXCEPTIONS)
    vrm_cmake_add_compiler_flag(HAS_FNO_EXCEPTIONS -fno-exceptions)
endif()

# Other compiler flags.
vrm_cmake_add_compiler_flag(HAS_PEDANTIC                          -pedantic)
vrm_cmake_add_compiler_flag(HAS_STDCXX1Y                          -std=c++1y)
vrm_cmake_add_compiler_flag(HAS_W                                 -W)
vrm_cmake_add_compiler_flag(HAS_WALL                              -Wall)
vrm_cmake_add_compiler_flag(HAS_WEXTRA                            -Wextra)
vrm_cmake_add_compiler_flag(HAS_WNO_UNUSED_LOCAL_TYPEDEFS         -Wno-unused-local-typedefs)
vrm_cmake_add_compiler_flag(HAS_WWRITE_STRINGS                    -Wwrite-strings)
vrm_cmake_add_compiler_flag(HAS_WSHADOW                           -Wshadow)
vrm_cmake_add_compiler_flag(HAS_WUNDEF                            -Wundef)
vrm_cmake_add_compiler_flag(HAS_WNO_MISSING_FIELD_INITIALIZERS    -Wno-missing-field-initializers)
vrm_cmake_add_compiler_flag(HAS_WPOINTER_ARITH                    -Wpointer-arith)
vrm_cmake_add_compiler_flag(HAS_WCAST_ALIGN                       -Wcast-align)
vrm_cmake_add_compiler_flag(HAS_WNO_UNREACHABLE_CODE              -Wno-unreachable-code)
vrm_cmake_add_compiler_flag(HAS_WNON_VIRTUAL_DTOR                 -Wnon-virtual-dtor)
vrm_cmake_add_compiler_flag(HAS_WOVERLOADED_VIRTUAL               -Woverloaded-virtual)

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
vrm_check_target()

# Setup subdirectories.
add_subdirectory(generator)
add_subdirectory(test)

# Create header-only install target (automatically glob)
vrm_cmake_header_only_install_glob("${VRM_PP_INC_DIR}" "include")