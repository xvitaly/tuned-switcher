/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
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

/**
 * Class for working with program settings.
*/
class SettingsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Get the geometry of the main window.
     * @returns Geometry of the main window.
    */
    QByteArray GetGeometry() const;

    /**
     * Set the geometry of the main window.
     * @param value New geometry value.
    */
    void SetGeometry(const QByteArray&);

    /**
     * Get the window state of the main window.
     * @returns Window state of the main window.
    */
    QByteArray GetWindowState() const;

    /**
     * Set the window state of the main window.
     * @param value New window state value.
    */
    void SetWindowState(const QByteArray&);

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
     * Save the program settings to file.
    */
    void Save();

    /**
     * Main constructor of the SettingsManager class.
     * @param parent Parent.
    */
    explicit SettingsManager(QObject* parent = nullptr);
protected:
    /**
     * Stores a pointer to the QSettings class instance.
    */
    QSettings* settings;

    /**
     * Stores the geometry of the main window option name.
    */
    const QString GeometryName = QStringLiteral("widget/geometry");

    /**
     * Stores the window state of the main window option name.
    */
    const QString WindowStateName = QStringLiteral("widget/windowState");

    /**
     * Stores the notification sound configuration option name.
    */
    const QString SoundEnabledName = QStringLiteral("widget/soundEnabled");
};

#endif // SETTINGSMANAGER_H
