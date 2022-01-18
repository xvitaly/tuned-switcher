#
# SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

if (BUILD_MANPAGE)
    find_program(
        Pandoc_EXECUTABLE
        NAMES pandoc
        DOC "Pandoc main executable"
        REQUIRED
    )
    mark_as_advanced(Pandoc_EXECUTABLE)
endif()
