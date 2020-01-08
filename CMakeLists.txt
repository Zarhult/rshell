CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if (POLICY CMP0048)
   # suppress warning
   cmake_policy(SET CMP0048 NEW)
endif()
PROJECT(rshell)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
   src/main.cpp
)

ADD_EXECUTABLE(test
   unit_tests/unit_test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest)
