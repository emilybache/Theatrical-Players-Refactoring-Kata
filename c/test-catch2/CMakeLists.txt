set(TEST_NAME sample_test_catch2)
include(FetchContent)
set(SOURCE_FILES main.cpp sample_catch.cpp)

# catch2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.10)
FetchContent_MakeAvailable(Catch2)

# approvals
FetchContent_Declare(
        ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp
        GIT_TAG        v.10.5.1)
FetchContent_MakeAvailable(ApprovalTests)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE ${SOURCE_FILES})
target_link_libraries(${TEST_NAME} src Catch2::Catch2 ApprovalTests::ApprovalTests)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
