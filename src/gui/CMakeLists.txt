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

set(INTERNAL_LIBS
    ${SOURCES}
    ${UI_HEADERS}
    ${HEADERS}
    ${MOC_HEADERS}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
    tuned-switcher-lib
)

add_executable(tuned-switcher-gui ${INTERNAL_LIBS})
target_link_libraries(tuned-switcher-gui PRIVATE ${EXTERNAL_LIBS})

install(TARGETS tuned-switcher-gui RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" BUNDLE DESTINATION "${CMAKE_INSTALL_BINDIR}")
