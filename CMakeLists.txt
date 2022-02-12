cmake_minimum_required(VERSION 3.5)
project(youtube_cpp_application VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})

set(ASSETS_DIR_NAME assets)

add_subdirectory(external/engine)

# youtube_cpp_application.exe
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} youtube_cpp_engine)
target_include_directories(${PROJECT_NAME} PRIVATE youtube_cpp_engine)


if (DEFINED ASSETS_DIR_NAME)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${ASSETS_DIR_NAME}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME})
endif()