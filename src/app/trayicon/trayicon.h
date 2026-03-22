/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
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
#include <QActionGroup>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QString>
#include <QStringLiteral>
#include <QHash>

#include "notificationsmanager/notificationsmanager.h"
#include "servicemanager/servicemanager.h"
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
     * "Service control" menu item clicked event slot (handler).
     * @param method Service control method name.
    */
    void serviceControlEvent(const TunedManager::ServiceMethod);

    /**
     * "Show settings" menu item clicked event slot (handler).
    */
    void showSettingsEvent();

    /**
     * "Show About form" menu item clicked event slot (handler).
    */
    void showAboutEvent();

    /**
     * "Exit application" menu item clicked event slot (handler).
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
     * Initialize the ServiceManager class instance.
    */
    void initializeService();

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
    void checkServiceRunning();

    /**
     * Check if the Tuned is not running and try to
     * start it with DBus methods.
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
     * Check whether the Tuned profile is running or not
     * and enable or disable various form controls.
    */
    void markServiceMode();

    /**
     * Set the notifications sound mode.
    */
    void setNotificationsMode();

    /**
     * Subscribe to DBus events.
    */
    void subscribeToEvents();

    /**
     * Exit the application immediately.
    */
    void exitApplication();

    QAction* getProfileAction(const QString&);

    /**
     * Create a menu entry for the "Auto-select profile" action.
     * @param parent Parent widget.
     * @returns Pointer to the QAction instance.
    */
    QAction* createAutoProfileAction(QWidget*);

    /**
     * Create a menu entry for the "Show About form" action.
     * @param parent Parent widget.
     * @returns Pointer to the QAction instance.
    */
    QAction* createAboutAction(QWidget*);

    /**
     * Create a menu entry for the "Show settings" action.
     * @param parent Parent widget.
     * @returns Pointer to the QAction instance.
    */
    QAction* createSettingsAction(QWidget*);

    /**
     * Create a menu entry for the "Quit application" action.
     * @param parent Parent widget.
     * @returns Pointer to the QAction instance.
    */
    QAction* createQuitAction(QWidget*);

    /**
     * Build and create submenu for service control functions.
     * @param parent Parent widget.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createServiceControlSubmenu(QWidget*);

    /**
     * Build and create a submenu with the list of available
     * Tuned profiles.
     * @param parent Parent widget.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createProfilesSubmenu(QWidget*);

    /**
     * Enumerate and add the available Tuned profiles to
     * the Profiles submenu.
     * @param parent Parent widget.
     * @returns Pointer to the QActionGroup instance.
    */
    QActionGroup* createProfilesMenuGroup(QWidget*);

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
     * Stores pointer to the ServiceManager class instance.
    */
    ServiceManager* serviceManager;

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
     * Stores a pointer to a group of the Tuned profiles QMenu
     * actions.
    */
    QActionGroup* profileActions;

    /**
     * Stores a pointer to the "Auto-select profile" menu action.
    */
    QAction* autoProfileAction;
};

#endif // TRAYICON_H
