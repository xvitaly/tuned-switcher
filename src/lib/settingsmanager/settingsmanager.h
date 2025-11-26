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
     * Get whether saving the widget geometry is enabled.
     * @returns Whether saving the widget geometry is enabled.
    */
    bool GetWidgetGeometryEnabled() const;

    /**
     * Set whether saving the widget geometry is enabled.
     * @param value Enable or disable saving the widget geometry.
    */
    void SetWidgetGeometryEnabled(const bool);

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
     * Get whether saving the widget form state is enabled.
     * @returns Whether saving the widget form state is enabled.
    */
    bool GetWidgetStateEnabled() const;

    /**
     * Set whether saving the widget form state is enabled.
     * @param value Enable or disable saving the widget form state.
    */
    void SetWidgetStateEnabled(const bool);

    /**
     * Get the state of the widget form.
     * @returns State of the widget form.
    */
    QByteArray GetWidgetState() const;

    /**
     * Set the state of the widget form.
     * @param value New widget form state value.
    */
    void SetWidgetState(const QByteArray&);

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
private:
    /**
     * Stores a pointer to the QSettings class instance.
    */
    QSettings* settings;

    /**
     * Stores whether saving the widget geometry is enabled.
    */
    const QString WidgetGeometryEnabledName = QStringLiteral("widget/saveGeometry");

    /**
     * Stores the geometry of the widget form option name.
    */
    const QString WidgetGeometryName = QStringLiteral("widget/geometry");

    /**
     * Stores whether saving the widget form state is enabled.
    */
    const QString WidgetStateEnabledName = QStringLiteral("widget/saveState");

    /**
     * Stores the state of the widget form option name.
    */
    const QString WidgetStateName = QStringLiteral("widget/state");

    /**
     * Stores the notification sound configuration option name.
    */
    const QString SoundEnabledName = QStringLiteral("common/soundEnabled");
};

#endif // SETTINGSMANAGER_H
