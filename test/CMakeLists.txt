cmake_minimum_required(VERSION 3.8)

set(this Test)

set(sources
        Test.cpp
)

add_executable(${this} ${sources} ../LM_OMS.h ../LMOMS.cpp)

target_link_libraries(${this} PUBLIC
    gtest_main
    ${LHFT}
)

add_test(
    NAME ${this}
    COMMAND ${this}
)
