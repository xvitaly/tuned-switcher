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
    explicit Settings(QWidget *parent = nullptr);
    
    /**
     * Destructor of the Settings class.
    */
    ~Settings();

private:
    /**
     * Stores the GUI application form instance.
    */
    Ui::Settings *ui;
};

#endif // SETTINGS_H
