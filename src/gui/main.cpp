/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file main.cpp
 * This file contains main entry point implementation.
*/

#include "mainwindow/mainwindow.h"
#include "translationmanager/translationmanager.h"

/**
 * The main entry point.
 * @param argc Command-line arguments count.
 * @param argv Command-line arguments array.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setDesktopFileName(QT_STRINGIFY(TS_LAUNCHER_NAME));

    TranslationManager *translator = new TranslationManager();
    a.installTranslator(translator -> GetQtTranslator());
    a.installTranslator(translator -> GetAppTranslator());

    MainWindow w;
    w.show();

    return a.exec();
}
