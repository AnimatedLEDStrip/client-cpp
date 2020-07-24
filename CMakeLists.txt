#  Copyright (c) 2019-2020 AnimatedLEDStrip
#
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.

cmake_minimum_required(VERSION 3.5)
project(AnimatedLEDStripClient LANGUAGES CXX)
set(AnimatedLEDStripClient_VERSION_MAJOR 0)
set(AnimatedLEDStripClient_VERSION_MINOR 6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG_ON)

set(CMAKE_CXX_FLAGS="-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS="-lgcov")
find_package(Threads REQUIRED)

include(CTest)

include(ExternalProject)

# Dependencies

set(JSON_VERSION v3.7.3)
set(JSON_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/nlohmann)
set(JSON_HEADER ${JSON_SRC_DIR}/json.hpp)
file(DOWNLOAD https://github.com/nlohmann/json/releases/download/${JSON_VERSION}/json.hpp ${JSON_HEADER})

set(SAFE_MAP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/safe-map)
file(DOWNLOAD https://github.com/KarenRei/safe-map/raw/master/safemap.h ${SAFE_MAP_DIR}/safemap.h)
file(DOWNLOAD https://github.com/KarenRei/safe-map/raw/master/number.h ${SAFE_MAP_DIR}/number.h)
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/safe-map PROPERTIES COMPILE_FLAGS "-w")

# Testing

if (CMAKE_BUILD_TYPE STREQUAL Debug AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    # Download and unpack googletest at configure time
    configure_file(googletest.CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
            EXCLUDE_FROM_ALL)

    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif ()

    include(CodeCoverage.cmake)


    enable_testing()
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_LCOV_EXCLUDES '/usr/include/*' 'test/*' 'build/run/*' 'src/nlohmann/*' 'src/safe-map/*')
    SETUP_TARGET_FOR_COVERAGE_LCOV(
            NAME test_with_coverage
            EXECUTABLE test/run_tests
    )
    add_subdirectory(test)
endif ()

add_subdirectory(src)
