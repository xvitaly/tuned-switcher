/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GUIHELPERS_H
#define GUIHELPERS_H

/**
 * @file guihelpers/guihelpers.h
 * Contains the GuiHelpers class definition.
*/

#include <QObject>

class GuiHelpers : public QObject
{
    Q_OBJECT
public:
private:
    explicit GuiHelpers(QObject* parent = nullptr);
};

#endif // GUIHELPERS_H
