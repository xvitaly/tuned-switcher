#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QObject>

#include "tunedtypes/tunedtypes.h"

class TunedManager : public QObject
{
    Q_OBJECT
public:
    explicit TunedManager(QObject *parent = nullptr);
    QString GetActiveProfile();
    QStringList GetAvailableProfiles();
    QTunedProfileList GetAvailableProfiles2();
    bool SetActiveProfile(const QString&);
private:
    const QString BusName = "com.redhat.tuned";
    const QString BusPath = "/Tuned";
    const QString BusInterface = "com.redhat.tuned.control";
    const QString BusProfileNameActive = "active_profile";
    const QString BusProfileNameAvailable = "profiles";
    const QString BusProfileNameSwitch = "switch_profile";
    const QString BusProfileChanged = "profile_changed";
    const QString BusProfileNameAvailable2 = "profiles2";
    const QDBusConnection DBusInstance = QDBusConnection::systemBus();
private slots:
    void ProfileChangedEvent(const QString&, const bool, const QString&);
signals:
    void ProfileChangedSignal(const QString&, const bool, const QString&);
};

#endif // TUNEDMANAGER_H
