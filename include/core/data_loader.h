#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <QObject>
#include <QReadWriteLock>
#include "world.h"

class QNetworkAccessManager;
class QNetworkReply;
class QDir;
class QFile;


class CDataLoader : public QObject
{
    Q_OBJECT
public:
    CDataLoader(QObject* parent = nullptr);

    CWorld::TShPtrWorld getCurrentWorld() const;


public Q_SLOTS:
    void loadMapFromServer( const QString& server );
//    void loadLocalFileData( const QString& server );



Q_SIGNALS:
    void finished();
    void serverUnavailable();
private:
    Q_DISABLE_COPY(CDataLoader)
    QSharedPointer<QFile> m_currentFile;

    QNetworkAccessManager* m_networkManager;
    QReadWriteLock m_locker;
    CWorld::TShPtrWorld m_currWorld;

    Q_SLOT void mapDownloaded( QNetworkReply* );
    QDir getDataDirectory() const;

    void closeCurrentFile();

};

#endif // DATA_LOADER_H
