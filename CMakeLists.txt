cmake_minimum_required(VERSION 3.14)
project(mini_query_lang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile_commands.json (for VS Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Prevent overriding parent project compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(tokenizer_tests
    tests/tokenizer_tests.cpp
)

target_include_directories(tokenizer_tests PRIVATE src)
target_link_libraries(tokenizer_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tokenizer_tests)