# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# Add a custom target for the unit tests.
add_custom_target(tests COMMENT "Build all the unit tests.")

# Tests depend on generator.
add_dependencies(tests generator_run)

# `check` depends on `tests`.
add_dependencies(check tests)

# Adds a test, also as part of the `tests` target.
function(vrm_pp_add_unit_test name)
    vrm_pp_add_test(${ARGV})
    add_dependencies(tests ${name})
endfunction()

# Adds a test for a public header, making sure including it works properly.
function(vrm_pp_add_header_test header)
    string(REGEX REPLACE "/" "." _target "${header}")
    
    if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp")
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp" "
            #include <${header}>
            int main() { }
        ")
    endif()

    add_executable(test.header.${_target} EXCLUDE_FROM_ALL
                        "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp")
    
    vrm_pp_add_test(test.header.${_target}
                            ${CMAKE_CURRENT_BINARY_DIR}/test.header.${_target})
    
    add_dependencies(tests test.header.${_target})
endfunction()

# Glob all tests.
file(GLOB_RECURSE VRM_PP_TEST_SOURCES "*.cpp")

# Glob all public headers. (Detail headers can be removed here.)
file(GLOB_RECURSE VRM_PP_PUBLIC_HEADERS "${VRM_PP_SOURCE_DIR}/include/*.hpp")
vrm_pp_list_remove_glob(VRM_PP_PUBLIC_HEADERS GLOB_RECURSE
    "dummy")

# Include directories.
include_directories(${VRM_PP_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Generate tests that include each public header.
foreach(_header IN LISTS VRM_PP_PUBLIC_HEADERS)
    file(RELATIVE_PATH _relative "${VRM_PP_SOURCE_DIR}/include" "${_header}")
    vrm_pp_add_header_test("${_relative}")
endforeach()

# Add all the unit tests.
foreach(_file IN LISTS VRM_PP_TEST_SOURCES)
    file(READ "${_file}" _contents)
    vrm_pp_target_name_for(_target "${_file}")

    add_executable(${_target} EXCLUDE_FROM_ALL "${_file}")
    vrm_pp_add_unit_test(${_target} ${CMAKE_CURRENT_BINARY_DIR}/${_target})    
endforeach()

# TODO: extract macros/funcs