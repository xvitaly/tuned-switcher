#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
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

qt_add_resources(RESOURCES
    resources.qrc
)

qt_wrap_ui(UI_HEADERS
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
    Qt::Widgets
    Qt::DBus
    ${LIB_NAME}
)

add_executable(${APP_NAME}
    ${INTERNAL_LIBS}
)

if (Qt6_FOUND)
    qt_add_translations(${APP_NAME}
        TS_FILES ${TRANSLATIONS}
        QM_FILES_OUTPUT_VARIABLE QM_FILES
    )
else()
    qt_add_translation(QM_FILES
        ${TRANSLATIONS}
    )
    add_custom_target(${I18N_NAME} ALL DEPENDS ${QM_FILES})
endif()

target_link_libraries(${APP_NAME} PRIVATE
    ${EXTERNAL_LIBS}
)

install(TARGETS ${APP_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    BUNDLE DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/translations
)
