#ifndef DATA_HOLDER_H
#define DATA_HOLDER_H

#include <QList>
#include "world.h"

class CDataHolder
{
public:
    CDataHolder();
    QList<CWorld::TShPtrWorld> m_worlds;

    typedef QMap<QString,bool> TMapServerZoneAvailability;
    typedef QMap<QString, TMapServerZoneAvailability> TMapServersAvailability;

    TMapServersAvailability m_servers;

    QStringList getServersList() const;

private:
    Q_DISABLE_COPY(CDataHolder)
    void fillServers();
    void addServerToRuZone(const QString&);

};


#endif // DATA_HOLDER_H
