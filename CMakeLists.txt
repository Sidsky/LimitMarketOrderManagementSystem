cmake_minimum_required(VERSION 3.8)
project(LHFT)

set(CMAKE_CXX_STANDARD 20)

add_executable(LHFT main.cpp LM_OMS.h LMOMS.cpp)
add_subdirectory(lib/googletest)
add_subdirectory(test)

set (headers
        LM_OMS.h
)

set (src
        LMOMS.cpp)

add_library(${LHFT} STATIC ${headers} ${src})

enable_testing()

