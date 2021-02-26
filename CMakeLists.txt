cmake_minimum_required(VERSION 3.10)

project(tuned-switcher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Settings.cmake)
include(cmake/External.cmake)

include_directories("src/lib")
include_directories("src/gui")
include_directories("src/tray")

add_subdirectory("src/lib")
add_subdirectory("src/gui")
add_subdirectory("src/tray")
