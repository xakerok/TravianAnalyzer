#include "core/data_holder.h"

#include <QMap>
#include <QStringList>

CDataHolder::CDataHolder()
{
    fillServers();
}

QStringList CDataHolder::getServersList() const
{
    QStringList serversList;
    foreach ( TMapServerZoneAvailability currZone, m_servers.values() )
    {
        foreach( QString currServerName, currZone.keys() )
            serversList.append( currServerName );
    }
    return serversList;
}



void CDataHolder::fillServers()
{
    addServerToRuZone("ts1");
    addServerToRuZone("ts2");
    addServerToRuZone("ts3");
    addServerToRuZone("ts4");
    addServerToRuZone("ts5");
    addServerToRuZone("ts6");
    addServerToRuZone("ts7");
    addServerToRuZone("ts8");
    addServerToRuZone("test");
    addServerToRuZone("tx2");
}

void CDataHolder::addServerToRuZone(const QString &serverName)
{
    const QString zone = "ru";
    const QString fullServerName = serverName+".travian."+zone;
    if( m_servers.contains( zone ) )
    {
        if( !m_servers.value(zone).contains( serverName ) )
        {
            TMapServerZoneAvailability currZone = m_servers.value(zone);
            currZone.insert(fullServerName, true);
            m_servers.insert(zone, currZone );
        }
    }
    else
    {
        TMapServerZoneAvailability currZone;
        currZone.insert(fullServerName, true);
        m_servers.insert(zone, currZone );
    }
}
