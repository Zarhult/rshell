cmake_minimum_required(VERSION 2.6)

if (POLICY CMP0048)
   # suppress warning
   cmake_policy(SET CMP0048 NEW)
endif()
project(rshell)

add_subdirectory(googletest)

set(CMAKE_CXX_STANDARD 11)

add_executable(rshell
   src/main.cpp
   src/connectorand.cpp
   src/connectoror.cpp
   src/connectorpipe.cpp
   src/connectorsemicolon.cpp
   src/exe.cpp
   src/nightmare.cpp
   src/parser.cpp
   src/test.cpp
)

add_executable(test
   unit_tests/unit_test.cpp
   src/connectorand.cpp
   src/connectoror.cpp
   src/connectorpipe.cpp
   src/connectorsemicolon.cpp
   src/exe.cpp
   src/nightmare.cpp
   src/parser.cpp
   src/test.cpp
)

if(MSVC)
    target_compile_options(rshell PRIVATE /W4 /WX)
else()
    target_compile_options(rshell PRIVATE -Wall -Wextra -pedantic)
endif()

target_link_libraries(test gtest)
target_compile_definitions(test PRIVATE gtest)
