#include "tunedmanager.h"

QString TunedManager::GetActiveProfile()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QString> DBusReply = DBusInterface.call(BusProfileNameActive);
    return DBusReply.value();
}

QStringList TunedManager::GetAvailableProfiles()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(BusProfileNameAvailable);
    return DBusReply.value();
}

bool TunedManager::SetActiveProfile(QString Profile)
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<void> DBusReply = DBusInterface.call(BusProfileNameSwitch, Profile);
    return DBusReply.isValid();
}

void TunedManager::ProfileChangedEvent(QString NewProfile, bool SwitchResult)
{
    if (SwitchResult) emit ProfileChangedSignal(NewProfile);
}

TunedManager::TunedManager(QObject *parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
        QDBusConnection::systemBus().connect(BusName, BusPath, BusInterface, BusProfileChanged, this, SLOT(ProfileChangedEvent(QString, bool)));
}
