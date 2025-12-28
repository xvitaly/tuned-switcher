/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file guihelpers/guihelpers.cpp
 * Contains the GuiHelpers namespace implementation.
*/

#include <QPoint>
#include <QRect>
#include <QScreen>
#include <QWidget>

#include "guihelpers/guihelpers.h"

QPoint GuiHelpers::GetDefaultFormPosition(const QWidget* widget)
{
    return widget -> screen() -> availableGeometry().center() - widget -> frameGeometry().center();
}
