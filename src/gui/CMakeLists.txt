#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    mainwindow/mainwindow.cpp
    main.cpp
)

set(HEADERS
    mainwindow/mainwindow.h
)

qt5_wrap_ui(UI_HEADERS
    mainwindow/mainwindow.ui
)

qt5_add_resources(QRES
    ../../resources/tuned-switcher.qrc)

set(INTERNAL_LIBS
    ${SOURCES}
    ${UI_HEADERS}
    ${HEADERS}
    ${MOC_HEADERS}
    ${QRES}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
    tuned-lib
)

add_executable(tuned-gui ${INTERNAL_LIBS})
target_link_libraries(tuned-gui PRIVATE ${EXTERNAL_LIBS})
