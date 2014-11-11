#include "data_holder.h"

#include <QMap>
#include <QStringList>

CDataHolder::CDataHolder()
{
	fillAllServers();
}

void CDataHolder::clearData()
{
	m_locker.lockForRead();
	m_listServers.clear();
	m_locker.unlock();
}

void CDataHolder::fillAllServers()
{
	addServer("ts1", "ru");
	addServer("ts2", "ru");
	addServer("ts3", "ru");
	addServer("ts4", "ru");
	addServer("ts5", "ru");
	addServer("ts6", "ru");
	addServer("ts7", "ru");
	addServer("ts8", "ru");
	addServer("tx3", "ru");
	addServer("test", "ru");
	addServer("tx2", "ru");
}

void CDataHolder::addServer(const QString &serverName, const QString &zone)
{
	m_locker.lockForRead();
	const QString fullServerName = serverName+".travian."+zone;
	TShPtrServer currServer = TShPtrServer( new CServer( fullServerName ) );
	Q_ASSERT( !m_listServers.contains( currServer ) );
	m_listServers.append( currServer );
	m_locker.unlock();
}


