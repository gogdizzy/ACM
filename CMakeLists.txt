cmake_minimum_required(VERSION 3.10)
project(ACM)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    message("ccache found")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif (CCACHE_FOUND)

include_directories(/usr/local/include)
find_package(Boost)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    message(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
endif ()

add_executable(main main.cpp)
