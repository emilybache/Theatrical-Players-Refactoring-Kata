cmake_minimum_required(VERSION 3.4...3.14)
project(theatrical_players_refactoring_kata
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(theatrical_players_lib STATIC
    "statement.cpp"
    "statement.h"
)

target_include_directories(
    theatrical_players_lib
    PUBLIC
    third_party
)

enable_testing()
add_subdirectory(tests)
