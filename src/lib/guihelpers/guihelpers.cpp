/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file guihelpers/guihelpers.cpp
 * Contains the GuiHelpers namespace implementation.
*/

#include <QByteArray>
#include <QIcon>
#include <QPixmap>
#include <QRect>
#include <QScreen>
#include <QSize>
#include <QString>
#include <QStringLiteral>
#include <QStyle>
#include <QVariant>
#include <QWidget>

#include "appconstants/appconstants.h"
#include "guihelpers/guihelpers.h"

QRect GuiHelpers::GetDefaultFormPosition(const QWidget* widget)
{
    return QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, widget -> size(), widget -> screen() -> availableGeometry());
}

bool GuiHelpers::CheckGeometryValid(const QByteArray& geometry)
{
    const QVariant result(geometry);
    return result.isValid() && result.toBool();
}

QIcon GuiHelpers::GetApplicationIcon()
{
    return QIcon::fromTheme(AppConstants::DomainSchemeName(), QIcon(QStringLiteral(":/icons/fallback.png")));
}

QPixmap GuiHelpers::GetApplicationPixmap(const int size)
{
    const QIcon icon = GetApplicationIcon();
    return icon.pixmap(icon.actualSize(QSize(size, size)));
}
