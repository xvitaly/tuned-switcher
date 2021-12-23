#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

file(GLOB TRANSLATIONS "i18n/${CMAKE_PROJECT_NAME}_*.ts")

install(FILES "icons/icon.svg" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps" RENAME "${SCHEME_NAME}.svg")

foreach(ICON_SIZE 16 22 24 32 48 64 128 256)
    install(FILES "icons/icon-${ICON_SIZE}.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps" RENAME "${SCHEME_NAME}.png")
endforeach()

configure_file("desktop/${CMAKE_PROJECT_NAME}.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.desktop" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${LAUNCHER_NAME}")

if (BUILD_DOC)
    doxygen_add_docs(${DOCS_NAME} src docs ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMENT "Building documentation with Doxygen.")
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()

if (BUILD_MANPAGE)
    configure_file("manpage/${CMAKE_PROJECT_NAME}.md.in" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.md" @ONLY)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1" COMMAND "${Pandoc_EXECUTABLE}" ARGS "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.md" -s -t man -o "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1" COMMENT "Building manpage using Pandoc." VERBATIM)
    add_custom_target(${MAN_NAME} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.1" DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
endif()

if (BUILD_TESTS)
    add_test(NAME test-desktop COMMAND ${DesktopFileValidate_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.desktop")
    add_test(NAME test-metainfo COMMAND ${AppstreamUtil_EXECUTABLE} validate "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.metainfo.xml")
endif()

configure_file("metainfo/${CMAKE_PROJECT_NAME}.metainfo.xml.in" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.metainfo.xml" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.metainfo.xml" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/metainfo" RENAME "${APPDATA_MANIFEST}")
