# CMakeList.txt : CMake project for rlv3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add the dependency directory.
add_subdirectory(Dependencies)

# Add source to this project's executable.
add_executable (rlv3 rlv3.cpp u-util.cpp data.cpp)
target_include_directories(rlv3 PRIVATE ./)

target_link_libraries(rlv3 spdlog sol)

# TODO: Add tests and install targets if needed.
