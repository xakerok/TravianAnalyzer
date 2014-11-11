#include "core/servers_model.h"
#include "data_holder.h"
#include "helper/server_helper.h"


CServersModel::CServersModel( CDataHolder* holder, QObject *parent): QAbstractListModel( parent ),
	m_holder( holder )
{

}

int CServersModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED( parent );
	CServerHelper helper;
	return helper.getAllServers(m_holder).size();
}

QVariant CServersModel::data(const QModelIndex &index, int role) const
{
	checkIndexValid( index );
	CServerHelper helper;
	if( role == Qt::DisplayRole || role == sNameRole )
		return helper.getAllServers(m_holder).at( index.row() )->getServerName();
	else
		return QVariant();
}


QStringList CServersModel::getAllServersName() const
{
	CServerHelper helper;
	QStringList serversName;
	foreach ( TShPtrConstServer server, helper.getAllServers(m_holder) )
	{
		serversName.append( server->getServerName() );
	}
	return serversName;
}
void CServersModel::checkIndexValid(const QModelIndex &index) const
{
	Q_ASSERT( index.isValid() );
	Q_ASSERT( index.row() >= 0);
	Q_ASSERT( index.row() < rowCount() );
	Q_ASSERT( index.column() == 0 );
	Q_UNUSED( index );
}
