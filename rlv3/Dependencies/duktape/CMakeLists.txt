# CMakeLists.txt : Duktape library

# Add static library
add_library(duktape STATIC duktape.c)
target_include_directories(duktape PUBLIC ./)