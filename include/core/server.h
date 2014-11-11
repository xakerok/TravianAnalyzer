#ifndef SERVER_H
#define SERVER_H

#include "world.h"


class CServer
{
	public:

		CServer( const QString& serverName );

//		int rowCount(const QModelIndex &parent) const;
//		QVariant data(const QModelIndex &index, int role) const;

		QString getServerName() const;
		double getServerVersion() const;

		void addWorld( CWorld::TShPtrWorld newWorld );
		bool contains( const QDateTime& worldTime );

	private:
		QString m_serverName;
		double m_version;
		QList<CWorld::TShPtrWorld> m_listWorlds;

};

typedef QSharedPointer< const CServer > TShPtrConstServer;
typedef QSharedPointer<CServer> TShPtrServer;
typedef QList<TShPtrServer> TListShPtrServer;




#endif // SERVER_H
