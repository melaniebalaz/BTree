cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

find_package(Threads REQUIRED)

enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -DDEBUG_TESTS=1")

file(GLOB BTREE_SRC
        #"../include/Node.h"
        #"../include/Btree.h"
        "../include/Container.h"
        "../upload/Btree.h"
        )
file(GLOB TESTS_SRC
        "btreeTests.cpp")
add_executable(runAllTests main.cpp ${TESTS_SRC} ${BTREE_SRC} )

target_link_libraries(runAllTests
        gtest
        gtest_main
        )

add_test(AllTests runAllTests)
