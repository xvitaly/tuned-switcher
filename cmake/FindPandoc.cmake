#
# SPDX-FileCopyrightText: 2021-2023 EasyCoding Team and contributors
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

    function(pandoc_build_manpage SrcName DestName)
        add_custom_command(
            OUTPUT "${DestName}"
            COMMAND "${Pandoc_EXECUTABLE}"
            ARGS "${SrcName}" -s -t man -o "${DestName}"
            DEPENDS "${SrcName}"
            COMMENT "Building manpage using Pandoc."
            VERBATIM
        )
    endfunction()
endif()
