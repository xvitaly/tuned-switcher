/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

/**
 * @file guihelpers/guihelpers.h
 * Contains the GuiHelpers namespace definition.
*/

#include <QPoint>
#include <QWidget>

/**
 * Namespace with static methods for working with GUI.
*/
namespace GuiHelpers
{
    /**
     * Get the default form position at the center of the screen.
    */
    QPoint GetDefaultFormPosition(const QWidget*);
}

#endif // GUIHELPERS_H
