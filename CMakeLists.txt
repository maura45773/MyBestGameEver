cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Project)

add_subdirectory(libs/SFML)

set(SRC Main.cpp Hero.h)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window)