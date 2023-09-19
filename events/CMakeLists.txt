cmake_minimum_required(VERSION 3.0.0)
if (CMAKE_VERSION VERSION_GREATER "3.24.0")
		cmake_policy(SET CMP0135 NEW)
endif()

get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME ${CURRENT_DIR_NAME})

project(${PROJECT_NAME} C CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${PROJECT_NAME}_test
  ${PROJECT_NAME}.cpp
  ${PROJECT_NAME}_test.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${PROJECT_NAME}.cpp
  ${PROJECT_NAME}_main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
