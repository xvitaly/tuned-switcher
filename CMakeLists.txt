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

add_subdirectory("assets")
add_subdirectory("src")
