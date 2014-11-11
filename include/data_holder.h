#ifndef DATA_HOLDER_H
#define DATA_HOLDER_H

#include <QReadWriteLock>
#include "core/servers_model.h"

class CDataHolder
{
		friend class CServerHelper;
	public:
		CDataHolder();

	protected:
		void clearData();
		TListShPtrServer m_listServers;

	private:
		void fillAllServers();
		void addServer(const QString& serverName, const QString& zone);

		Q_DISABLE_COPY(CDataHolder)
		QReadWriteLock m_locker;

};


#endif // DATA_HOLDER_H
