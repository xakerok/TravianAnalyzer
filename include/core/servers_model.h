#ifndef SERVERS_MODEL_H
#define SERVERS_MODEL_H

#include <QAbstractListModel>
#include "server.h"

class CDataHolder;

class CServersModel : public QAbstractListModel
{
		Q_OBJECT
	public:
		CServersModel( CDataHolder*, QObject* parent = nullptr );

		enum
		{
			sNameRole = Qt::UserRole + 1
		} EServerRole;

		int rowCount(const QModelIndex &parent = QModelIndex() ) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole ) const;


		QStringList getAllServersName() const;

	private:
		Q_DISABLE_COPY(CServersModel)
		void checkIndexValid( const QModelIndex& ) const;

		CDataHolder* m_holder;
};

#endif // SERVERS_MODEL_H
