cmake_minimum_required(VERSION 3.14)
project(CameraPingPong VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt и OpenCV
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
file(GLOB_RECURSE ALL_HEADERS "src/*.h")
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(CameraPingPongLib ${ALL_SOURCES} ${ALL_HEADERS})
target_include_directories(CameraPingPongLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(CameraPingPongLib PUBLIC Qt5::Widgets ${OpenCV_LIBS})

add_executable(CameraPingPong src/main.cpp)
target_link_libraries(CameraPingPong PRIVATE CameraPingPongLib)

enable_testing()
add_subdirectory(tests)
