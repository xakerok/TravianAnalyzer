#include "core/data_loader.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QByteArray>
#include <QFile>
#include <QStandardPaths>
#include <QTimeZone>

#include "core/world.h"
#include "core/player.h"
#include "core/alliance.h"
#include "core/village.h"

QByteArray getNextValue(QByteArray& item)
{
    QByteArray ret = item.left( item.indexOf(char(44)) );
    item.remove(0, item.indexOf(char(44))+1 );
    return ret;
}

QByteArray getNextText(QByteArray& item)
{
    Q_ASSERT( item.at(0) == char(39) );
    QByteArray ret = item.left( item.indexOf(char(39),1) );
    item.remove(0, ret.size()+2 );
    ret.remove(0,1);
    return ret;
}

CDataLoader::CDataLoader(QObject *parent) : QObject(parent),
    m_currentFile( nullptr ),
    m_networkManager( nullptr ),
    m_currWorld( nullptr )
{

}

CWorld::TShPtrWorld CDataLoader::getCurrentWorld() const
{
    return m_currWorld;
}

void CDataLoader::loadMapFromServer( const QString &server )
{
    m_networkManager = new QNetworkAccessManager( parent() );

    bool bRes = connect( m_networkManager, &QNetworkAccessManager::finished,
                         this, &CDataLoader::mapDownloaded );
    Q_ASSERT( bRes );
    QNetworkRequest req( QUrl("http://" + server + "/map.sql"));
    m_networkManager->get( req );
}

void CDataLoader::mapDownloaded( QNetworkReply* reply )
{
    if( reply->error() != QNetworkReply::NoError )
    {
        qDebug() << reply->errorString();
        if( reply->error() == QNetworkReply::ContentNotFoundError )
            Q_EMIT serverUnavailable();
    }
    else
    {
        QByteArray loadedData = reply->readAll();

        if( !m_currWorld.isNull() )
        {
            if( m_currWorld->m_time ==
                    reply->header(QNetworkRequest::LastModifiedHeader).toDateTime() )
            {
                reply->deleteLater();
                Q_EMIT finished();
                return;
            }
            else
                m_currWorld.clear();
        }

        m_currWorld = CWorld::TShPtrWorld( new CWorld( reply->header(QNetworkRequest::LastModifiedHeader).toDateTime() ) ) ;

        foreach( QByteArray baCurrValue, loadedData.split( '\n') )
        {
            baCurrValue = baCurrValue.mid( baCurrValue.indexOf("(")+1 );
            baCurrValue = baCurrValue.left( baCurrValue.lastIndexOf(")") );
            if( baCurrValue.isEmpty() )
                break;

            uint field_id = getNextValue(baCurrValue).toUInt();
            Q_ASSERT( field_id != 0 );

            int v_x = getNextValue(baCurrValue).toInt();
            int v_y = getNextValue(baCurrValue).toInt();

            QString strPlayerTrib;
            int itrib = getNextValue(baCurrValue).toInt();

            switch (itrib)
            {
            case 1:
                strPlayerTrib = "Roman";
                break;
            case 2:
                strPlayerTrib = "Teuton";
                break;
            case 3:
                strPlayerTrib = "Gaul";
                break;
            case 4:
                strPlayerTrib = "Nature";
                break;
            case 5:
                strPlayerTrib = "Natars";
                break;
            default:
                Q_ASSERT_X(false, this->metaObject()->className(), "Invalid trib");
                break;
            }

            uint v_id = getNextValue(baCurrValue).toUInt();

            QString v_name = getNextText(baCurrValue);

            uint p_id = getNextValue(baCurrValue).toUInt();

            QString p_name = getNextText(baCurrValue);

            uint a_id = getNextValue(baCurrValue).toUInt();

            QString a_name = getNextText(baCurrValue);

            uint v_pop = baCurrValue.toUInt();

            if( m_currWorld->m_villages.find(field_id) == m_currWorld->m_villages.end() )
            {
                CWorld::TShPtrVillage currVillage = CWorld::TShPtrVillage( new CVillage );
                currVillage->m_x = v_x;
                currVillage->m_y = v_y;
                currVillage->m_villageName = v_name;
                currVillage->m_population = v_pop;
                m_currWorld->m_villages.insert( field_id, currVillage );

                CWorld::TShPtrPlayer currPlayer = CWorld::TShPtrPlayer( nullptr );
                if( m_currWorld->m_players.find(p_id) == m_currWorld->m_players.end() )
                {
                    currPlayer = CWorld::TShPtrPlayer( new CPlayer );
                    currPlayer->m_playerTribe = strPlayerTrib;
                    currPlayer->m_villages.insert( v_id, CPlayer::TWeakPtrVillage( currVillage)   );
                    currPlayer->m_playerName = p_name;
                }
                else
                {
                    currPlayer = m_currWorld->m_players.value( p_id );
                    if( currPlayer->m_villages.find( v_id ) == currPlayer->m_villages.end() )
                        currPlayer->m_villages.insert( v_id, CPlayer::TWeakPtrVillage( currVillage)   );
                    else
                        Q_ASSERT_X(false, "CDataLoader::mapDownloaded;", "Village already exist. Some error");
                }
                Q_ASSERT( !currPlayer.isNull() );

                if( a_id != 0 && currPlayer->m_alliance.toStrongRef().isNull() )
                {
                    CWorld::TShPtrAlliace currAlliance = CWorld::TShPtrAlliace( nullptr );
                    if( m_currWorld->m_alliaces.find( a_id ) == m_currWorld->m_alliaces.end() )
                    {
                        currAlliance = CWorld::TShPtrAlliace( new CAlliance );
                        currAlliance->m_allianceName = a_name;
                    }
                    else
                        currAlliance = m_currWorld->m_alliaces.value(a_id);

                    currPlayer->m_alliance = CPlayer::TWeakPtrAlliace( currAlliance );

                    if( !currAlliance->m_players.contains( CAlliance::TWeakPtrPlayer( currPlayer ) ))
                        currAlliance->m_players.append( CAlliance::TWeakPtrPlayer( currPlayer ) );

                    m_currWorld->m_alliaces.insert(a_id, currAlliance );
                }
                m_currWorld->m_players.insert(p_id, currPlayer );

            }
            else
                Q_ASSERT_X(false, "CDataLoader::mapDownloaded;", "Village already exist. Some error");

        }

        Q_EMIT finished();


        //        qDebug() << "ALLIES: ";
        //        foreach( CWorld::TShPtrAlliace ally, m_currWorld->m_alliaces.values() )
        //            qDebug() << ally->m_allianceName;

        //        qDebug() << "\nPLAYERS: ";
                foreach( CWorld::TShPtrPlayer player, m_currWorld->m_players.values() )
                    qDebug() << player->m_playerName;

                qDebug() << "\n";

        //        qDebug() << "\nVILLAGES: ";
//                foreach( CWorld::TShPtrVillage village, m_currWorld->m_villages.values() )
//                    qDebug() << "(" << village->m_x << "|" << village->m_y << ")" << village->m_villageName;


    }
    reply->deleteLater();

}

QDir CDataLoader::getDataDirectory() const
{
    QDir dir = QStandardPaths::writableLocation( QStandardPaths::DataLocation );
    if( !dir.exists() )
        dir.mkpath( dir.path() );
    return dir;
}

void CDataLoader::closeCurrentFile()
{
    m_currentFile->close();
    m_currentFile.clear();
}
