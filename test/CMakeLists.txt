# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup custom functions, master targets and file lists for the unit tests
##############################################################################
add_custom_target(tests COMMENT "Build all the unit tests.")
add_dependencies(check tests)

#   vrm_pp_add_unit_test(<name> ...)
#
# Equivalent to `vrm_pp_add_test`, except the test is also added as a
# dependency of the `tests` target.
function(vrm_pp_add_unit_test name)
    vrm_pp_add_test(${ARGV})
    add_dependencies(tests ${name})
endfunction()

#   vrm_pp_add_header_test(<header-name>)
#
# Add a unit test for the public header file `header-name`, which must be a
# relative path from Hana's include directory, e.g. `boost/hana/tuple.hpp`.
#
# This function creates an executable named `header.header-name` and a test
# of the same name. The only source file of the executable contains an empty
# `main` and it includes the `header-name` file. This is used to make sure
# that including any public header works properly. Also, the
# `header.header-name` target is made a dependency of the `headers` target.
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

# A list of all the test files
#
# Source files that are not available due to caveats are removed
# from this list below.
file(GLOB_RECURSE VRM_PP_TEST_SOURCES "*.cpp")

# A list of all the public headers
#
# Header files that are not available due to caveats are removed
# from this list below.
file(GLOB_RECURSE VRM_PP_PUBLIC_HEADERS "${VRM_PP_SOURCE_DIR}/include/*.hpp")
vrm_pp_list_remove_glob(VRM_PP_PUBLIC_HEADERS GLOB_RECURSE
    "${VRM_PP_SOURCE_DIR}/include/boost/hana/detail/*.hpp"
    "${VRM_PP_SOURCE_DIR}/include/boost/hana/ext/boost/fusion/detail/*.hpp")


##############################################################################
# Include directories
##############################################################################
include_directories(${VRM_PP_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})



##############################################################################
# Generate tests that include each public header
##############################################################################
foreach(_header IN LISTS VRM_PP_PUBLIC_HEADERS)
    file(RELATIVE_PATH _relative "${VRM_PP_SOURCE_DIR}/include" "${_header}")
    vrm_pp_add_header_test("${_relative}")
endforeach()


##############################################################################
# Add all the unit tests
##############################################################################
foreach(_file IN LISTS VRM_PP_TEST_SOURCES)
    file(READ "${_file}" _contents)
    vrm_pp_target_name_for(_target "${_file}")

    # If the file contains the special VRM_PP_TEST_PART marker, we split
    # it into several subparts. This is done to avoid long compile-times and
    # other inconveniences.
    if ("${_contents}" MATCHES "VRM_PP_TEST_PART == ([0-9]+)")
        string(REGEX MATCHALL "VRM_PP_TEST_PART == ([0-9]+)" _parts "${_contents}")
        string(REGEX REPLACE "VRM_PP_TEST_PART == ([0-9]+)" "\\1" _parts "${_parts}")
        list(REMOVE_DUPLICATES _parts)
        add_custom_target(${_target})

        foreach(n IN LISTS _parts)
            add_executable("${_target}.part${n}" EXCLUDE_FROM_ALL "${_file}")
            set_target_properties("${_target}.part${n}" PROPERTIES
                COMPILE_DEFINITIONS "VRM_PP_TEST_PART=${n}")
            add_dependencies(${_target} "${_target}.part${n}")

            vrm_pp_add_unit_test("${_target}.part${n}"
                ${CMAKE_CURRENT_BINARY_DIR}/${_target}.part${n})
        endforeach()
    else()
        add_executable(${_target} EXCLUDE_FROM_ALL "${_file}")
        vrm_pp_add_unit_test(${_target} ${CMAKE_CURRENT_BINARY_DIR}/${_target})
    endif()
endforeach()