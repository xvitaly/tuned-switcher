#
# SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# ======================================================
# =============== Project initialization ===============
# ======================================================

cmake_minimum_required(VERSION 3.28...4.0)

project(tuned-switcher
    VERSION 0.9.2
    DESCRIPTION "Performance profile manager"
    HOMEPAGE_URL "https://github.com/xvitaly/tuned-switcher"
    LANGUAGES CXX
)
set(RELEASE_DATE "2025-05-25")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# ======================================================
# ================== Project options ===================
# ======================================================

option(BUILD_DOC "Build and install API and application documentation in HTML format." OFF)
option(BUILD_MANPAGE "Build and install manpage with documentation." OFF)
option(BUILD_TESTS "Build various tests." OFF)
option(LINK_ALL_STATICALLY "Link the program against all libraries statically (no dependencies mode)." OFF)
option(LINK_ENABLE_OPTIMIZATIONS "Enable link-time optimizations if supported by current C++ compiler." OFF)

# ======================================================
# ==================== Target names ====================
# ======================================================

set(APP_NAME "${CMAKE_PROJECT_NAME}")
set(LIB_NAME "${CMAKE_PROJECT_NAME}-lib")
set(I18N_NAME "${CMAKE_PROJECT_NAME}-i18n")
set(DOCS_NAME "${CMAKE_PROJECT_NAME}-docs")
set(MAN_NAME "${CMAKE_PROJECT_NAME}-man")

# ======================================================
# ===================== File names =====================
# ======================================================

set(SCHEME_NAME "org.easycoding.TunedSwitcher")
set(LAUNCHER_FILE_NAME "${SCHEME_NAME}.desktop")
set(APPDATA_FILE_NAME "${SCHEME_NAME}.metainfo.xml")

# ======================================================
# ================= Internal imports ===================
# ======================================================

include(GNUInstallDirs)

# ======================================================
# ============= External custom imports ================
# ======================================================

include(cmake/FindPandoc.cmake)
include(cmake/FindTestHelpers.cmake)

# ======================================================
# =========== Link time optimizations checks ===========
# ======================================================

include(CheckIPOSupported)
include(CheckPIESupported)

check_ipo_supported(RESULT CMAKE_CXX_LINK_IPO_SUPPORTED LANGUAGES CXX)
check_pie_supported(LANGUAGES CXX)

# ======================================================
# ==================== Qt detection ====================
# ======================================================

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2.0
    REQUIRED
    COMPONENTS
        Core
        DBus
        Gui
        LinguistTools
        Widgets
)

# ======================================================
# ================= Doxygen detection ==================
# ======================================================

if (BUILD_DOC)
    find_package(Doxygen REQUIRED)
    set(DOXYGEN_PROJECT_LOGO "assets/icons/icon-64.png")
    set(DOXYGEN_QUIET YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_QT_AUTOBRIEF YES)
    set(DOXYGEN_MARKDOWN_SUPPORT YES)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_EXTRACT_PRIV_VIRTUAL YES)
    set(DOXYGEN_EXTRACT_PACKAGE YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_EXTRACT_LOCAL_CLASSES YES)
    set(DOXYGEN_EXTRACT_LOCAL_METHODS YES)
    set(DOXYGEN_SHOW_INCLUDE_FILES YES)
    set(DOXYGEN_BINARY_TOC YES)
    set(DOXYGEN_TOC_EXPAND YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "docs/README.md")
endif()

# ======================================================
# ================== Library target ====================
# ======================================================

set(LIBRARY_HEADERS
    src/lib/logcategories/logcategories.h
    src/lib/tunedtypes/tunedtypes.h
    src/lib/translationmanager/translationmanager.h
    src/lib/notificationsmanager/dbusconverters.h
    src/lib/notificationsmanager/notificationsmanager.h
    src/lib/tunedmanager/tunedmanager.h
)

set(LIBRARY_SOURCES
    src/lib/logcategories/logcategories.cpp
    src/lib/tunedtypes/tunedtypes.cpp
    src/lib/translationmanager/translationmanager.cpp
    src/lib/notificationsmanager/notificationsmanager.cpp
    src/lib/tunedmanager/tunedmanager.cpp
)

configure_file(
    src/lib/appconstants/appconstants.h.in
    generated/appconstants/appconstants.h
    @ONLY
)

add_library(${LIB_NAME} OBJECT
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCES}
)

target_include_directories(${LIB_NAME} PUBLIC
    src/lib
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Widgets
    Qt6::DBus
)

if (LINK_ENABLE_OPTIMIZATIONS AND CMAKE_CXX_LINK_IPO_SUPPORTED)
    set_target_properties(${LIB_NAME}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON
    )
endif()

if (LINK_ENABLE_OPTIMIZATIONS AND CMAKE_CXX_LINK_PIE_SUPPORTED)
    set_target_properties(${LIB_NAME}
        PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif()

if (LINK_ALL_STATICALLY)
    target_link_libraries(${LIB_NAME} PRIVATE
        -static
    )
endif()

# ======================================================
# ================= Application target =================
# ======================================================

set(APPLICATION_HEADERS
    src/app/trayicon/trayicon.h
    src/app/mainwindow/mainwindow.h
)

set(APPLICATION_SOURCES
    src/app/trayicon/trayicon.cpp
    src/app/mainwindow/mainwindow.cpp
    src/app/main.cpp
)

set(APPLICATION_RESOURCES
    src/app/resources.qrc
)

set(APPLICATION_UI_SOURCES
    src/app/mainwindow/mainwindow.ui
)

file(GLOB APPLICATION_TS_SOURCES "assets/i18n/${APP_NAME}_*.ts")

add_executable(${APP_NAME}
    ${APPLICATION_HEADERS}
    ${APPLICATION_SOURCES}
    ${APPLICATION_UI_SOURCES}
    ${APPLICATION_RESOURCES}
)

qt_add_translations(${APP_NAME}
    TS_FILES ${APPLICATION_TS_SOURCES}
    QM_FILES_OUTPUT_VARIABLE APPLICATION_QM_FILES
)

target_include_directories(${APP_NAME} PRIVATE
    src/app
)

target_link_libraries(${APP_NAME} PRIVATE
    Qt6::Widgets
    Qt6::DBus
    ${LIB_NAME}
)

if (LINK_ENABLE_OPTIMIZATIONS AND CMAKE_CXX_LINK_IPO_SUPPORTED)
    set_target_properties(${APP_NAME}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON
    )
endif()

if (LINK_ENABLE_OPTIMIZATIONS AND CMAKE_CXX_LINK_PIE_SUPPORTED)
    set_target_properties(${APP_NAME}
        PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif()

if (LINK_ALL_STATICALLY)
    target_link_libraries(${APP_NAME} PRIVATE
        -static
    )
endif()

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${APPLICATION_QM_FILES} DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${APP_NAME}/translations")

# ======================================================
# =================== Assets target ====================
# ======================================================

install(FILES "assets/icons/icon.svg" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps" RENAME "${SCHEME_NAME}.svg")

foreach(ICON_SIZE 16 22 24 32 48 64 128 256)
    install(FILES "assets/icons/icon-${ICON_SIZE}.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps" RENAME "${SCHEME_NAME}.png")
endforeach()

configure_file("assets/desktop/${APP_NAME}.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.desktop" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${LAUNCHER_FILE_NAME}")

configure_file("assets/metainfo/${APP_NAME}.metainfo.xml.in" "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.metainfo.xml" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.metainfo.xml" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/metainfo" RENAME "${APPDATA_FILE_NAME}")

if (BUILD_DOC)
    doxygen_add_docs(${DOCS_NAME} src docs ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMENT "Building documentation with Doxygen.")
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()

if (BUILD_MANPAGE)
    configure_file("assets/manpage/${APP_NAME}.md.in" "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.md" @ONLY)
    pandoc_build_manpage("${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.md" "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1")
    add_custom_target(${MAN_NAME} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1" DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
endif()

# ======================================================
# ==================== Tests target ====================
# ======================================================

if (BUILD_TESTS)
    enable_testing()
    add_test(NAME test-desktop COMMAND ${DesktopFileValidate_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.desktop")
    add_test(NAME test-metainfo COMMAND ${AppstreamUtil_EXECUTABLE} validate "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.metainfo.xml")
endif()
