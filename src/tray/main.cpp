/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "trayicon/trayicon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrayIcon *trayIcon = new TrayIcon();
    trayIcon -> Show();

    return a.exec();
}
