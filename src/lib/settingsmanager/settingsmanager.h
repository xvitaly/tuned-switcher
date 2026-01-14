/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

/**
 * @file settingsmanager/settingsmanager.h
 * Contains the SettingsManager class definition.
*/

#include <QByteArray>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringLiteral>

#include "autorunmanager/autorunmanager.h"

/**
 * Class for working with program settings.
*/
class SettingsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Get whether saving the form geometry is enabled.
     * @returns Whether saving the form geometry is enabled.
    */
    bool GetGeometrySavingEnabled() const;

    /**
     * Set whether saving the form geometry is enabled.
     * @param value Enable or disable saving the form geometry.
    */
    void SetGeometrySavingEnabled(const bool);

    /**
     * Get the geometry of the widget form.
     * @returns Geometry of the widget form.
    */
    QByteArray GetWidgetGeometry() const;

    /**
     * Set the geometry of the widget form.
     * @param value New widget form geometry value.
    */
    void SetWidgetGeometry(const QByteArray&);

    /**
     * Get the geometry of the settings form.
     * @returns Geometry of the settings form.
    */
    QByteArray GetSettingsGeometry() const;

    /**
     * Set the geometry of the settings form.
     * @param value New settings form geometry value.
    */
    void SetSettingsGeometry(const QByteArray&);

    /**
     * Get the geometry of the About form.
     * @returns Geometry of the About form.
    */
    QByteArray GetAboutGeometry() const;

    /**
     * Set the geometry of the About form.
     * @param value New About form geometry value.
    */
    void SetAboutGeometry(const QByteArray&);

    /**
     * Get the notification sound configuration.
     * @returns Notification sound configuration.
    */
    bool GetSoundEnabled() const;

    /**
     * Set the notification sound configuration.
     * @param value New notification sound configuration value.
    */
    void SetSoundEnabled(const bool);

    /**
     * Get whether the autorun feature is supported.
     * @returns Whether the autorun feature is supported.
    */
    bool IsAutorunSupported() const;

    /**
     * Get whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
    */
    bool GetAutorunEnabled() const;

    /**
     * Set whether the autorun feature is enabled.
     * @param value Enable or disable the autorun feature.
    */
    void SetAutorunEnabled(const bool) const;

    /**
     * Main constructor of the SettingsManager class.
     * @param parent Parent.
    */
    explicit SettingsManager(QObject* parent = nullptr);
private:
    /**
     * Stores a pointer to the QSettings class instance.
    */
    QSettings* settings;

    /**
     * Stores a pointer to the AutorunManager class instance.
    */
    AutorunManager* autorun;

    /**
     * Stores whether saving the form geometry is enabled.
    */
    const QString GeometrySavingEnabledName = QStringLiteral("common/saveGeometry");

    /**
     * Stores the geometry of the widget form option name.
    */
    const QString WidgetGeometryName = QStringLiteral("widget/geometry");

    /**
     * Stores the geometry of the settings form option name.
    */
    const QString SettingsGeometryName = QStringLiteral("settings/geometry");

    /**
     * Stores the geometry of the About form option name.
    */
    const QString AboutGeometryName = QStringLiteral("about/geometry");

    /**
     * Stores the notification sound configuration option name.
    */
    const QString SoundEnabledName = QStringLiteral("common/soundEnabled");
};

#endif // SETTINGSMANAGER_H
