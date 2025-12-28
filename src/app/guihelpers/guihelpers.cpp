/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file guihelpers/guihelpers.cpp
 * Contains the GuiHelpers class implementation.
*/

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QScreen>
#include <QWidget>

#include "guihelpers/guihelpers.h"

GuiHelpers::GuiHelpers(QObject* parent) : QObject(parent)
{}

QPoint GuiHelpers::GetDefaultFormPosition(QWidget* widget)
{
    return widget -> screen() -> availableGeometry().center() - widget -> frameGeometry().center();
}
