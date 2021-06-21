#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.10)

project(tuned-switcher
    VERSION 0.2.1
    DESCRIPTION "Simple utility to manipulate the Tuned service"
    HOMEPAGE_URL "https://github.com/EasyCoding/tuned-switcher"
    LANGUAGES CXX
)
set(RELEASE_DATE "2021-06-21")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Variables.cmake)
include(cmake/Settings.cmake)
include(cmake/External.cmake)

if (BUILD_APPLET OR BUILD_GUI)
    include_directories("src/lib")
    add_subdirectory("src/lib")
    add_subdirectory("assets")
else()
    message(FATAL_ERROR "Nothing to build. Please select at least one component.")
endif()

if (BUILD_APPLET)
    include_directories("src/tray")
    add_subdirectory("src/tray")
endif()

if (BUILD_GUI)
    include_directories("src/gui")
    add_subdirectory("src/gui")
endif()
