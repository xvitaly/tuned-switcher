/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef ABOUT_H
#define ABOUT_H

/**
 * @file about/about.h
 * Contains the About class definition.
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
    class About;
}

/**
 * Class for working with the About form.
*/
class About : public QDialog
{
    Q_OBJECT
public:
    /**
     * Main constructor of the About class.
     * @param parent Parent widget.
    */
    explicit About(QWidget* parent = nullptr);

    /**
     * Destructor of the About class.
    */
    ~About();

private slots:
    /**
     * Form closed event slot (handler).
    */
    void formClosedEvent();

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
     * Save form settings to file: position and size.
    */
    void saveFormSettings();

    /**
     * Set the default form position to the center of the screen.
    */
    void setDefaultFormPosition();

    /**
     * Set custom form style.
    */
    void setFormStyle();

    /**
     * Set custom form controls.
    */
    void setFormControls();

    /**
     * Initialize and connect the events for the form.
    */
    void setFormEvents();

    /**
     * Stores the GUI application form instance.
    */
    Ui::About* ui;

    /**
     * Stores pointer to the SettingsManager class instance.
    */
    SettingsManager* settings;
};

#endif // ABOUT_H
