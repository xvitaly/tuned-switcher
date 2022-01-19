#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

set(QT_COMPONENTS
    Core
    DBus
    Gui
    LinguistTools
    Widgets
)

find_package(Qt6 6.2.0
    COMPONENTS ${QT_COMPONENTS}
    QUIET
)

if (NOT Qt6_FOUND)
    find_package(Qt5 5.15.0
        COMPONENTS ${QT_COMPONENTS}
        REQUIRED
    )
endif()
