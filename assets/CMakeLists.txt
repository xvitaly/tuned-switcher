#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

install(FILES "icons/icon.svg" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps" RENAME "${SCHEME_NAME}.svg")
install(FILES "icons/icon-16.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-22.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/22x22/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-24.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/24x24/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-32.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-48.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/48x48/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-64.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/64x64/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-128.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/128x128/apps" RENAME "${SCHEME_NAME}.png")
install(FILES "icons/icon-256.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/256x256/apps" RENAME "${SCHEME_NAME}.png")

if (BUILD_APPLET)
    configure_file("desktop/applet.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/applet.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${SCHEME_NAME}.Applet.desktop")
endif()

if (BUILD_GUI)
    configure_file("desktop/gui.desktop.in" "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gui.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications" RENAME "${SCHEME_NAME}.desktop")
endif()

install(FILES "metainfo/${CMAKE_PROJECT_NAME}.metainfo.xml" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/metainfo" RENAME "${SCHEME_NAME}.metainfo.xml")
