add_executable(tests
    test_statement.cpp
)

target_include_directories(
    tests
    PUBLIC
    ../third_party
    ..
)

target_link_libraries(tests
    PRIVATE theatrical_players_lib
)

add_test(
    NAME ${PROJECT_NAME}_test
    COMMAND tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
