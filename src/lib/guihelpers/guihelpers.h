/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

/**
 * @file guihelpers/guihelpers.h
 * Contains the GuiHelpers namespace definition.
*/

#include <QByteArray>
#include <QIcon>
#include <QPixmap>
#include <QRect>
#include <QWidget>

/**
 * Namespace with static methods for working with GUI.
*/
namespace GuiHelpers
{
    /**
     * Get the default form position at the center of the screen.
     * @param widget Widget instance.
     * @returns Form position at the center of the screen.
    */
    QRect GetDefaultFormPosition(const QWidget*);

    /**
     * Check whether the geometry value is valid.
     * @param geometry The geometry value for checking.
     * @returns The geometry value check result.
     * @retval true The geometry value is valid.
     * @retval false The geometry value is not valid.
    */
    bool CheckGeometryValid(const QByteArray&);

    /**
     * Get the application icon from the installed theme or form
     * the included resource.
     * @returns The application icon.
    */
    QIcon GetApplicationIcon();

    /**
     * Get the application icon from the installed theme or form
     * the included resource as a pixmap.
     * @param size The desired icon size.
     * @returns The application icon as a pixmap.
    */
    QPixmap GetApplicationPixmap(const int);
}

#endif // GUIHELPERS_H
