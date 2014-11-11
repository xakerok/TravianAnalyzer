#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H

#include <QtGlobal>

class CDataHolder;
class CServersModel;
#include "core/server.h"

class CServerHelper
{
		friend class CServersModel;
	public:
		TListShPtrServer getAllServers(CDataHolder*);

	private:
		CServerHelper();
		Q_DISABLE_COPY(CServerHelper)

};

#endif // SERVER_HELPER_H
