#include "core/server.h"
#include "config.h"


CServer::CServer(const QString& serverName )
{
	m_serverName = serverName;
	m_version = DEFAULT_TRAVIAN_VERSION;
}


QString CServer::getServerName() const
{
	return m_serverName;
}

double CServer::getServerVersion() const
{
	return m_version;
}

void CServer::addWorld( CWorld::TShPtrWorld newWorld )
{
	if( !contains( newWorld->m_time ) )
		m_listWorlds.append( newWorld );
}

bool CServer::contains( const QDateTime& worldTime )
{
	if( m_listWorlds.isEmpty() )
		return false;

	foreach (CWorld::TShPtrConstWorld world, m_listWorlds)
	{
		if( world->m_time == worldTime )
			return true;
	}
	return false;
}

