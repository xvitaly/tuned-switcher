#!/bin/sh
#
# SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
set -e

lupdate-qt6 \
    -locations relative \
    ../../src/ -ts tuned-switcher_*.ts -no-obsolete

sed \
    -r \
    -e "s/language=\"([a-z]{2,})_([A-Z]{2,})\"/language=\"\1\"/g" \
    -e "2i <!--\nSPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors\nSPDX-License-Identifier: GPL-3.0-or-later\n-->" \
    -i tuned-switcher_*.ts
