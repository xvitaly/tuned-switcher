#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

set(CMAKE_AUTOMOC ON)

set(SOURCES
    tunedtypes/tunedtypes.cpp
    translationmanager/translationmanager.cpp
    notificationsmanager/notificationsmanager.cpp
    tunedmanager/tunedmanager.cpp
)

set(HEADERS
    tunedtypes/tunedtypes.h
    translationmanager/translationmanager.h
    notificationsmanager/dbusconverters.h
    notificationsmanager/notificationsmanager.h
    tunedmanager/tunedmanager.h
)

configure_file(
    "appconstants/appconstants.h.in"
    "generated/appconstants/appconstants.h"
    @ONLY
)

set(INTERNAL_LIBS
    ${SOURCES}
    ${HEADERS}
    ${MOC_HEADERS}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
)

add_library(${LIB_NAME} STATIC
    ${INTERNAL_LIBS}
)

target_include_directories(${LIB_NAME} PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
)

target_link_libraries(${LIB_NAME} PRIVATE
    ${EXTERNAL_LIBS}
)
