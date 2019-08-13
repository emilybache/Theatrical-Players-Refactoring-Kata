project(tests)

add_executable(${PROJECT_NAME}
    ../statement.cpp
    ../statement.h
    test_statement.cpp
    main.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ../third_party ..)

enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})