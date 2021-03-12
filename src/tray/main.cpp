/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "trayicon/trayicon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setDesktopFileName(QT_STRINGIFY(TS_LAUNCHER_NAME));

    QTranslator qtTranslator;
    qtTranslator.load(QLocale(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load(QLocale(), "tuned-switcher", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&appTranslator);

    TrayIcon *trayIcon = new TrayIcon();
    trayIcon -> Show();

    return a.exec();
}
