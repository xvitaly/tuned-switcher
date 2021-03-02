#include "tunedmanager.h"

QString TunedManager::GetActiveProfile()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QString> DBusReply = DBusInterface.call(BusMethodNameActiveProfile);
    return DBusReply.value();
}

QStringList TunedManager::GetAvailableProfiles()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(BusMethodNameProfiles);
    return DBusReply.value();
}

QTunedProfileMode TunedManager::GetProfileMode()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedProfileMode> DBusReply = DBusInterface.call(BusMethodNameProfileMode);
    return DBusReply.value();
}

bool TunedManager::IsProfileModeAuto()
{
    const QTunedProfileMode ProfileMode = GetProfileMode();
    return ProfileMode.Mode == "auto";
}

QTunedResult TunedManager::SetProfileModeAuto()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(BusMethodNameAutoProfile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedResult TunedManager::SetActiveProfile(const QString& Profile)
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(BusMethodNameSwitchProfile, Profile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedProfileList TunedManager::GetAvailableProfiles2()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedProfileList> DBusReply = DBusInterface.call(BusMethodNameProfiles2);
    return DBusReply.value();
}

void TunedManager::ProfileChangedEvent(const QString& NewProfile, const bool SwitchResult, const QString& ResultMessage)
{
    emit ProfileChangedSignal(NewProfile, SwitchResult, ResultMessage);
}

TunedManager::TunedManager(QObject *parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qRegisterMetaType<QTunedProfile>("QTunedProfile");
        qDBusRegisterMetaType<QTunedProfile>();
        qRegisterMetaType<QTunedProfileList>("QTunedProfileList");
        qDBusRegisterMetaType<QTunedProfileList>();
        qRegisterMetaType<QTunedProfileMode>("QTunedProfileMode");
        qDBusRegisterMetaType<QTunedProfileMode>();
        qRegisterMetaType<QTunedResult>("QTunedResult");
        qDBusRegisterMetaType<QTunedResult>();
        QDBusConnection::systemBus().connect(BusName, BusPath, BusInterface, BusSignalNameProfileChanged, this, SLOT(ProfileChangedEvent(const QString&, const bool, const QString&)));
    }
}
