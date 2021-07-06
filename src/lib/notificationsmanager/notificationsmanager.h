/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef NOTIFICATIONSMANAGER_H
#define NOTIFICATIONSMANAGER_H

/** @file lib/notificationsmanager/notificationsmanager.h
 * This file contains NotificationsManager class structure.
*/

#include <QObject>

class NotificationsManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationsManager(QObject *parent = nullptr);

signals:

};

#endif // NOTIFICATIONSMANAGER_H
