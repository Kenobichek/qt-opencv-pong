cmake_minimum_required(VERSION 3.5)

project(CameraPingPong)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(OpenCV REQUIRED)

add_executable(CameraPingPong src/main.cpp)

target_link_libraries(CameraPingPong Qt5::Widgets ${OpenCV_LIBS})
