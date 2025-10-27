cmake_minimum_required(VERSION 3.5)

project(CameraPingPong)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRC
	"src/*.cpp"
	"src/*/*.cpp"
)

add_executable(CameraPingPong ${SRC})

target_link_libraries(CameraPingPong Qt5::Widgets ${OpenCV_LIBS})
