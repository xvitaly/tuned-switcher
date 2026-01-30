/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PORTALREQUEST_H
#define PORTALREQUEST_H

/**
 * @file portalrequest/portalrequest.h
 * Contains the PortalRequest class definition.
*/

#include <QObject>

class PortalRequest : public QObject
{
    Q_OBJECT
public:
    explicit PortalRequest(QObject* parent = nullptr);
};

#endif // PORTALREQUEST_H
