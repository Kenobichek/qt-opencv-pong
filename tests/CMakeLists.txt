include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

file(GLOB TEST_SOURCES "*.cpp")

add_executable(CameraPingPongTests ${TEST_SOURCES})
target_link_libraries(CameraPingPongTests PRIVATE gtest_main CameraPingPongLib)

gtest_discover_tests(CameraPingPongTests)
