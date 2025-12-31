/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file guihelpers/guihelpers.cpp
 * Contains the GuiHelpers namespace implementation.
*/

#include <QByteArray>
#include <QPoint>
#include <QRect>
#include <QScreen>
#include <QVariant>
#include <QWidget>

#include "guihelpers/guihelpers.h"

QPoint GuiHelpers::GetDefaultFormPosition(const QWidget* widget)
{
    return widget -> screen() -> availableGeometry().center() - widget -> frameGeometry().center();
}

bool GuiHelpers::CheckGeometryValid(const QByteArray& geometry)
{
    const QVariant result(geometry);
    return result.isValid() && result.toBool();
}
