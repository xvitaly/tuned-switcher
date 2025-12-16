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
     * Stores the GUI application form instance.
    */
    Ui::About* ui;
};

#endif // ABOUT_H
