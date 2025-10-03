/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRAYICON_H
#define TRAYICON_H

/**
 * @file trayicon/trayicon.h
 * Contains the TrayIcon class definition.
*/

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QString>
#include <QStringLiteral>
#include <QHash>

#include "notificationsmanager/notificationsmanager.h"
#include "settingsmanager/settingsmanager.h"
#include "tunedmanager/tunedmanager.h"

/**
 * Class for working with the Applet application.
*/
class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    /**
     * Main constructor of the TrayIcon class.
     * @param parent Parent widget.
    */
    explicit TrayIcon(QWidget* parent = nullptr);

    /**
     * Show the system tray icon.
    */
    void Show();
private slots:
    /**
     * "Tuned profile selected" event slot (handler).
     * @param action System tray menu action, caused this event.
    */
    void profileSelectedEvent(QAction*);

    /**
     * "Auto-select profile" clicked event slot (handler).
     * @param autoMode "Auto-select profile" mode on or off.
    */
    void profileAutoSelectedEvent(const bool);

    /**
     * "Tuned profile changed" DBus event slot (handler).
     * @param profile Recently switched profile name.
     * @param result Switch result: true - success; false - failure.
     * @param message Result message (OK on success).
    */
    void profileChangedEvent(const QString&, const bool, const QString&);

    /**
     * "Enable profiles" clicked event slot (handler).
     * @param autoMode "Enable profiles" mode on or off.
    */
    void serviceEnabledEvent(const bool);

    /**
     * "Exit application" event slot (handler).
    */
    void exitEvent();
private:
    /**
     * Initialize the SettingsManager class instance.
    */
    void initializeSettings();

    /**
     * Initialize the NotificationsManager class instance.
    */
    void initializeNotifications();

    /**
     * Initialize the TunedManager class instance.
    */
    void initializeTuned();

    /**
     * Try to start the Tuned service if not running.
    */
    void tryToStartTuned();

    /**
     * Check if the Tuned service is not running and
     * try to start it with DBus methods.
    */
    void checkTunedRunning();

    /**
     * Create an instance of the QSystemTrayIcon and set
     * its properties.
    */
    void setTrayIcon();

    /**
     * Get the active Tuned profile and mark it.
    */
    void markCurrentProfile();

    /**
     * Change the "Auto-select profile" mode checkbox.
     * @param autoMode New "Auto-select profile" mode value.
    */
    void setAutoProfileMode(const bool);

    /**
     * Check if the automatic mode is enabled and mark the
     * special checkbox.
    */
    void markAutoProfileMode();

    /**
     * Subscribe to DBus events.
    */
    void subscribeToEvents();

    /**
     * Exit the application immediately.
    */
    void exitApplication();

    /**
     * Build and create submenu for various settings.
     * @param parent Parent widget.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createSettingsSubmenu(QWidget*);

    /**
     * Build and create submenu with the list of available
     * Tuned profiles.
     * @param parent Parent widget.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createProfilesSubmenu(QWidget*);

    /**
     * Build and create menu for the system tray icon.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createTrayIconMenu();

    /**
     * Stores pointer to the QSystemTrayIcon class instance.
    */
    QSystemTrayIcon* trayIcon;

    /**
     * Stores pointer to the SettingsManager class instance.
    */
    SettingsManager* settings;

    /**
     * Stores pointer to the NotificationsManager class instance.
    */
    NotificationsManager* notifications;

    /**
     * Stores pointer to the TunedManager class instance.
    */
    TunedManager* tunedManager;

    /**
     * Stores special hash table with the Tuned profiles and
     * assigned QMenu elements.
    */
    QHash<QString, QAction*> tunedProfiles;

    /**
     * Stores the name of the "Auto-select profile" action.
    */
    const QString autoProfileActionName = QStringLiteral("//autoselect//profile//action//");
};

#endif // TRAYICON_H
