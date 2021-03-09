/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mainwindow/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(QLocale(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load(QLocale(), "tuned-switcher", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
