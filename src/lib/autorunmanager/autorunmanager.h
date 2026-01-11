/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef AUTORUNMANAGER_H
#define AUTORUNMANAGER_H

/**
 * @file autorunmanager/autorunmanager.h
 * Contains the AutorunManager class definition.
*/

#include <QObject>

class AutorunManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the AutorunManager class.
     * @param parent Parent.
    */
    explicit AutorunManager(QObject* parent = nullptr);
private:
};

#endif // AUTORUNMANAGER_H
