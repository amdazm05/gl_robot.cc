cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
project(gl_robot)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    robot_enviroment
    STATIC
    ${PROJECT_SOURCE_DIR}/src/enviroment/robotrender.cc 
    ${PROJECT_SOURCE_DIR}/src/enviroment/robotwindow.cc 
)

target_link_directories(
    robot_enviroment
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/enviroment
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/app/main.cc
)


target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    robot_enviroment
    glfw
    GL
    GLEW
)

add_executable(example
    ${PROJECT_SOURCE_DIR}/app/example.cc
)

target_link_libraries(
    example
    PUBLIC
    glfw
    GL
    GLEW
)