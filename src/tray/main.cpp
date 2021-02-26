#include "trayicon/trayicon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrayIcon *trayIcon = new TrayIcon();
    trayIcon -> Show();

    return a.exec();
}
