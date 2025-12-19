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
     * Set custom form style.
    */
    void setFormStyle();

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
