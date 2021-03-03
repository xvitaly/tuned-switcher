#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

install(FILES "icons/icon.svg" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps" RENAME "${SCHEME_NAME}.svg")

foreach(ICON_SIZE 16 22 24 32 48 64 128 256)
    install(FILES "icons/icon-${ICON_SIZE}.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps" RENAME "${SCHEME_NAME}.png")
endforeach(loop_var)

if (BUILD_APPLET)
    configure_file("desktop/applet.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${SCHEME_NAME}.Applet.desktop")
endif()

if (BUILD_GUI)
    configure_file("desktop/gui.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${SCHEME_NAME}.desktop")
endif()

install(FILES "metainfo/${CMAKE_PROJECT_NAME}.metainfo.xml" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/metainfo" RENAME "${SCHEME_NAME}.metainfo.xml")
