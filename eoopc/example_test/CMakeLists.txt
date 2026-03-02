cmake_minimum_required(VERSION 3.10)
project(eoopc_testcase VERSION 1.0.0 LANGUAGES C)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "./*.c")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../inc)