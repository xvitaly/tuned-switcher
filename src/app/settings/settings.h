/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * @file settings/settings.h
 * Contains the Settings class definition.
*/

#include <QDialog>
#include <QWidget>

#include "settingsmanager/settingsmanager.h"

/**
 * UI namespace.
*/
namespace Ui {
    /**
     * GUI application form elements.
    */
    class Settings;
}

/**
 * Class for working with the program settings.
*/
class Settings : public QDialog
{
    Q_OBJECT
public:
    /**
     * Main constructor of the Settings class.
     * @param parent Parent widget.
    */
    explicit Settings(QWidget* parent = nullptr);
    
    /**
     * Destructor of the Settings class.
    */
    ~Settings();

private slots:
    /**
     * Settings accepted event slot (handler).
    */
    void settingsAcceptedEvent();

    /**
     * Settings rejected event slot (handler).
    */
    void settingsRejectedEvent();

private:
    /**
     * Initialize the SettingsManager class instance.
    */
    void initializeSettings();

    /**
     * Load form settings from file: position and size.
    */
    void loadFormSettings();

    /**
     * Load application settings from file.
    */
    void loadSettings();

    /**
     * Save form settings to file: position and size.
    */
    void saveFormSettings();

    /**
     * Save application settings to file.
    */
    void saveSettings();

    /**
     * Set the default form position to the center of the screen.
    */
    void setDefaultFormPosition();

    /**
     * Set custom form style.
    */
    void setFormStyle();

    /**
     * Initialize and connect the events for the form.
    */
    void setFormEvents();

    /**
     * Stores the GUI application form instance.
    */
    Ui::Settings* ui;

    /**
     * Stores pointer to the SettingsManager class instance.
    */
    SettingsManager* settings;
};

#endif // SETTINGS_H
