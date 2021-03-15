#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

file(GLOB TRANSLATIONS "i18n/${CMAKE_PROJECT_NAME}_*.ts")
qt5_add_translation(QM_FILES ${TRANSLATIONS})
add_custom_target(${I18N_NAME} ALL DEPENDS ${QM_FILES})
install(FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/translations)

install(FILES "icons/icon.svg" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps" RENAME "${SCHEME_NAME}.svg")

foreach(ICON_SIZE 16 22 24 32 48 64 128 256)
    install(FILES "icons/icon-${ICON_SIZE}.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps" RENAME "${SCHEME_NAME}.png")
endforeach()

if (BUILD_APPLET)
    configure_file("desktop/applet.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${APPLET_LAUNCHER}")
endif()

if (BUILD_GUI)
    configure_file("desktop/gui.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${GUI_LAUNCHER}")
endif()

if (BUILD_DOC)
    doxygen_add_docs(${DOCS_NAME} src docs ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMENT "Building documentation with Doxygen.")
endif()

configure_file("metainfo/${CMAKE_PROJECT_NAME}.metainfo.xml.in" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.metainfo.xml" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.metainfo.xml" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/metainfo" RENAME "${APPDATA_MANIFEST}")
