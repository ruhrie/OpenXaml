cmake_minimum_required(VERSION 3.5)

find_package( OpenGL REQUIRED )

message("Building dependencies")
add_subdirectory("Dependencies")