#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

find_package(Qt6 6.2
    COMPONENTS
        Widgets
        Core
        Gui
        DBus
        LinguistTools
    QUIET
)

if (NOT Qt6_FOUND)
    find_package(Qt5 5.15
        COMPONENTS
            Widgets
            Core
            Gui
            DBus
            LinguistTools
        REQUIRED
    )
endif()
