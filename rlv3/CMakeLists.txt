# CMakeList.txt : CMake project for rlv3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


#
# Configuration Section
#
include(CheckIncludeFileCXX)
check_include_file_cxx(dirent.h HAVE_DIRENT)
check_include_file_cxx(windows.h HAVE_WINDOWS)
check_include_file_cxx(sys/types.h HAVE_SYS_TYPES)
# Wait for filesystem to stabalize properly
#check_include_file_cxx(filesystem HAVE_FILESYSTEM)
#if(NOT HAVE_FILESYSTEM)
#	check_include_file_cxx(experimental/filesystem HAVE_FILESYSTEM_EXP)
#endif()
configure_file(config.h.in config.h)


#
# End Configuration
#




# Add the dependency directory.
add_subdirectory(Dependencies)

# Add source to this project's executable.
add_executable (rlv3 rlv3.cpp u-util.cpp data.cpp u-file.cpp)
target_include_directories(rlv3 PRIVATE ./)
target_include_directories(rlv3 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(rlv3 spdlog sol)
add_custom_command(TARGET rlv3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        $<TARGET_FILE_DIR:rlv3>)

# TODO: Add tests and install targets if needed.
