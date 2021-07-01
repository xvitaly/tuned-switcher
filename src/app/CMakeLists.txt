#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    trayicon/trayicon.cpp
    mainwindow/mainwindow.cpp
    main.cpp
)

set(HEADERS
    trayicon/trayicon.h
    mainwindow/mainwindow.h
)

qt5_add_resources(RESOURCES
    resources.qrc
)

qt5_wrap_ui(UI_HEADERS
    mainwindow/mainwindow.ui
)

set(INTERNAL_LIBS
    ${SOURCES}
    ${UI_HEADERS}
    ${HEADERS}
    ${MOC_HEADERS}
    ${RESOURCES}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
    ${LIB_NAME}
)

add_executable(${APP_NAME}
    ${INTERNAL_LIBS}
)

add_dependencies(${APP_NAME}
    ${I18N_NAME}
)

target_link_libraries(${APP_NAME} PRIVATE
    ${EXTERNAL_LIBS}
)

install(TARGETS ${APP_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    BUNDLE DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
