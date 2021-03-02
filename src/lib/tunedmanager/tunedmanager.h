#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QObject>
#include <stdexcept>

#include "tunedtypes/tunedtypes.h"

class TunedManager : public QObject
{
    Q_OBJECT
public:
    explicit TunedManager(QObject *parent = nullptr);
    QString GetActiveProfile();
    QStringList GetAvailableProfiles();
    QTunedProfileList GetAvailableProfiles2();
    QTunedProfileMode GetProfileMode();
    bool IsProfileModeAuto();
    QTunedResult SetProfileModeAuto();
    QTunedResult SetActiveProfile(const QString&);
private:
    const QString BusName = "com.redhat.tuned";
    const QString BusPath = "/Tuned";
    const QString BusInterface = "com.redhat.tuned.control";
    const QString BusMethodNameActiveProfile = "active_profile";
    const QString BusMethodNameProfiles = "profiles";
    const QString BusMethodNameSwitchProfile = "switch_profile";
    const QString BusMethodNameProfileMode = "profile_mode";
    const QString BusMethodNameAutoProfile = "auto_profile";
    const QString BusSignalNameProfileChanged = "profile_changed";
    const QString BusMethodNameProfiles2 = "profiles2";
    const QDBusConnection DBusInstance = QDBusConnection::systemBus();
private slots:
    void ProfileChangedEvent(const QString&, const bool, const QString&);
signals:
    void ProfileChangedSignal(const QString&, const bool, const QString&);
};

#endif // TUNEDMANAGER_H
