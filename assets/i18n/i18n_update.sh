#!/bin/sh
#
# SPDX-FileCopyrightText: 2021-2023 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
set -e

lupdate-qt5 \
    -locations relative \
    ../../src/ -ts tuned-switcher_*.ts -no-obsolete
