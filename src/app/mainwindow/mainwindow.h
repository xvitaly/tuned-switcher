/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow/mainwindow.h
 * Contains the MainWindow class definition.
*/

#include <QCloseEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <QStringList>
#include <QWidget>

#include "notificationsmanager/notificationsmanager.h"
#include "tunedmanager/tunedmanager.h"

/**
 * UI namespace.
*/
namespace Ui
{
    /**
     * GUI application form elements.
    */
    class MainWindow;
}

/**
 * Class for working with the GUI application.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Main constructor of the MainWindow class.
     * @param parent Parent widget.
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Destructor of the MainWindow class.
    */
    ~MainWindow();

protected slots:
    /**
     * Mouse move event slot (handler).
     * @param event Event object instance.
    */
    void mouseMoveEvent(QMouseEvent*);

    /**
     * Mouse button press event slot (handler).
     * @param event Event object instance.
    */
    void mousePressEvent(QMouseEvent*);

    /**
     * Mouse button release event slot (handler).
     * @param event Event object instance.
    */
    void mouseReleaseEvent(QMouseEvent*);

    /**
     * Form close event slot (handler).
     * @param event Event object instance.
    */
    void closeEvent(QCloseEvent*);

    /**
     * Key pressed event slot (handler).
     * @param event Event object instance.
    */
    void keyPressEvent(QKeyEvent*);

private slots:
    /**
     * "Tuned profile changed" DBus event slot (handler).
     * @param profile Recently switched profile name.
     * @param result Switch result: true - success; false - failure.
     * @param message Result message (OK on success).
    */
    void profileChangedEvent(const QString&, const bool, const QString&);

    /**
     * "Profile selected" event slot (handler).
     * @param profile Profile name.
    */
    void profileSelectedEvent(const QString&);

    /**
     * Button "Close form" clicked event slot (handler).
    */
    void closeFormEvent();

    /**
     * Checkbox "Auto-select profile" clicked event slot (handler).
     * @param modeAuto Auto-mode on or off.
    */
    void profileAutoSelectedEvent(bool);

private:
    /**
     * Initialize the NotificationsManager class instance.
    */
    void initializeNotifications();

    /**
     * Initialize the TunedManager class instance.
    */
    void initializeTuned();

    /**
     * Initialize and connect the events for the form.
    */
    void setFormEvents();

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
     * Get available Tuned profiles for internal usage.
    */
    void getTunedProfiles();

    /**
     * Subscribe to DBus events.
    */
    void subscribeToEvents();

    /**
     * Check if the automatic mode is enabled and mark the
     * special checkbox.
    */
    void markAutoProfileMode();

    /**
     * Load form settings: position and size.
    */
    void loadSettings();

    /**
     * Save form settings: position and size.
    */
    void saveSettings();

    /**
     * Set custom form style: remove border, apply gradients, etc.
    */
    void setFormStyle();

    /**
     * Get the active Tuned profile and set it on form.
    */
    void markCurrentProfile();

    /**
     * Change the "Auto-select profile" mode checkbox on the form.
     * @param mode New mode.
    */
    void setAutoProfileMode(bool);

    /**
     * Exit the application immediately.
    */
    void exitApplication();

    /**
     * Stores the GUI application form instance.
    */
    Ui::MainWindow *ui;

    /**
     * Stores pointer to the NotificationsManager class instance.
    */
    NotificationsManager *notifications;

    /**
     * Stores pointer to the TunedManager class instance.
    */
    TunedManager *tunedManager;

    /**
     * Stores the list of available Tuned profiles.
    */
    QStringList availableProfiles;

    /**
     * Stores the last mouse position.
    */
    QPoint mLastMousePosition;

    /**
     * Stores the form moving state.
    */
    bool mMoving;
};

#endif // MAINWINDOW_H
