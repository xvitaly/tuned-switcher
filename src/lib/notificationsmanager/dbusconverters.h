/**
 * SPDX-FileCopyrightText: 2010 David Sansome <me@davidsansome.com>
 * SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CONVERTERS_H
#define CONVERTERS_H

/** @file lib/notificationsmanager/dbusconverters.h
 * This file contains functions for automatic marshaling of a QImage
 * for the org.freedesktop.Notifications.Notify DBus method.
 *
 * These functions copied from the Clementine project and licensed under
 * the terms of GNU General Public License, version 3 or later.
*/

#include <QDBusArgument>
#include <QIcon>

/**
 * Overloaded operator << for the QImage DBus type.
 * @param argument QDBusArgument instance.
 * @param image QImage instance.
*/
QDBusArgument& operator <<(QDBusArgument &argument, const QImage &image)
{
    if (image.isNull())
    {
        argument.beginStructure();
        argument << 0 << 0 << 0 << false << 0 << 0 << QByteArray();
        argument.endStructure();
        return argument;
    }

    QImage scaled = image.scaledToHeight(100, Qt::SmoothTransformation);
    scaled = scaled.convertToFormat(QImage::Format_ARGB32);

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    // ABGR -> ARGB
    QImage i = scaled.rgbSwapped();
#else
    // ABGR -> GBAR
    QImage i(scaled.size(), scaled.format());
    for (int y = 0; y < i.height(); ++y)
    {
        QRgb *p = (QRgb *)scaled.scanLine(y);
        QRgb *q = (QRgb *)i.scanLine(y);
        QRgb *end = p + scaled.width();
        while (p < end)
        {
            *q = qRgba(qGreen(*p), qBlue(*p), qAlpha(*p), qRed(*p));
            p++;
            q++;
        }
    }
#endif

    argument.beginStructure();
    argument << i.width();
    argument << i.height();
    argument << i.bytesPerLine();
    argument << i.hasAlphaChannel();
    int channels = i.isGrayscale() ? 1 : (i.hasAlphaChannel() ? 4 : 3);
    argument << i.depth() / channels;
    argument << channels;
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
    argument << QByteArray(reinterpret_cast<const char *>(i.bits()), i.byteCount());
#else
    argument << QByteArray(reinterpret_cast<const char *>(i.bits()), i.sizeInBytes());
#endif
    argument.endStructure();
    return argument;
}

/**
 * Overloaded operator >> for the QImage DBus type.
 * @param argument QDBusArgument instance.
*/
const QDBusArgument& operator >>(const QDBusArgument& argument, QImage&)
{
    Q_ASSERT(0);
    return argument;
}

#endif // CONVERTERS_H
