#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <QObject>
#include <QReadWriteLock>
#include "core/server.h"

class QNetworkAccessManager;
class QNetworkReply;
class QDir;
class QFile;


class CDataLoader : public QObject
{
		Q_OBJECT
	public:
		CDataLoader(QObject* parent = nullptr);
		~CDataLoader();

		TShPtrServer getCurrentServer() const;


	public Q_SLOTS:
		void loadMapFromServer( const QString& serverName );
		//    void loadLocalFileData( const QString& server );

	Q_SIGNALS:
		void finished();
		void serverUnavailable();
	private:
		Q_DISABLE_COPY(CDataLoader)
		//    QSharedPointer<QFile> m_currentFile;

		QSharedPointer<QNetworkAccessManager> m_spNetworkManager;
		//    QReadWriteLock m_locker;
		TShPtrServer m_currServer;

		Q_SLOT void mapDownloaded( QNetworkReply* );
		//    QDir getDataDirectory() const;

		//    void closeCurrentFile();

};

#endif // DATA_LOADER_H
