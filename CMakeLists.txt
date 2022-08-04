#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.12)

project(tuned-switcher
    VERSION 0.7.1
    DESCRIPTION "Simple utility to manipulate the Tuned service"
    HOMEPAGE_URL "https://github.com/EasyCoding/tuned-switcher"
    LANGUAGES CXX
)
set(RELEASE_DATE "2022-08-04")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Variables.cmake)
include(cmake/Settings.cmake)
include(cmake/External.cmake)

if (BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory("assets")
add_subdirectory("src")
