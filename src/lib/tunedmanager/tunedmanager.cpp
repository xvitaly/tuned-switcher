#include "tunedmanager.h"

QString TunedManager::GetActiveProfile()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QString> DBusReply = DBusInterface.call(BusMethodNameActiveProfile);
    if (!DBusReply.isValid()) throw std::exception();
    return DBusReply.value();
}

QStringList TunedManager::GetAvailableProfiles()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(BusMethodNameProfiles);
    if (!DBusReply.isValid()) throw std::exception();
    return DBusReply.value();
}

QTunedProfileMode TunedManager::GetProfileMode()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedProfileMode> DBusReply = DBusInterface.call(BusMethodNameProfileMode);
    if (!DBusReply.isValid()) throw std::exception();
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
    if (!DBusReply.isValid()) throw std::exception();
    return DBusReply.value();
}

QTunedResult TunedManager::SetActiveProfile(const QString& Profile)
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(BusMethodNameSwitchProfile, Profile);
    if (!DBusReply.isValid()) throw std::exception();
    return DBusReply.value();
}

QTunedProfileList TunedManager::GetAvailableProfiles2()
{
    QDBusInterface DBusInterface(BusName, BusPath, BusInterface, DBusInstance);
    QDBusReply<QTunedProfileList> DBusReply = DBusInterface.call(BusMethodNameProfiles2);
    if (!DBusReply.isValid()) throw std::exception();
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
