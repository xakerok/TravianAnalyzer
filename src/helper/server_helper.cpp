#include "helper/server_helper.h"
#include "data_holder.h"

TListShPtrServer CServerHelper::getAllServers(CDataHolder* holder)
{
	return holder->m_listServers;
}

CServerHelper::CServerHelper()
{

}


