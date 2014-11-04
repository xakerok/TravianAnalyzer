#include "gui/main_window.h"
#include "ui_main_window.h"

#include <QDebug>
#include <QCompleter>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_loaderThread = QSharedPointer<QThread>(new QThread);
    m_loader = QSharedPointer<CDataLoader>(new CDataLoader);

    m_loader->moveToThread( m_loaderThread.data() );

    bool bRes = connect( m_loader.data(), &CDataLoader::finished,
                         this, &CMainWindow::loadThread_finished );
    Q_ASSERT( bRes );

    bRes = connect( m_loader.data(), &CDataLoader::serverUnavailable,
                         this, &CMainWindow::loadThread_unavailableServer );
    Q_ASSERT( bRes );


    m_loaderThread->start();

    readyToDownload();
    m_ui->cbServerSelector->addItems( m_holder.getServersList() );
    m_ui->cbServerSelector->setCurrentIndex(8);
}

CMainWindow::~CMainWindow()
{
    delete m_ui;
    m_loaderThread->quit();
    m_loaderThread->wait();
    m_loaderThread.clear();
    m_loader.clear();
}

void CMainWindow::on_pbLoadMap_clicked()
{
    m_ui->pbLoadMap->setDisabled( true );
    m_ui->cbServerSelector->setDisabled( true );
    m_ui->pbLoadMap->setText(tr("Loading..."));
    m_loader->loadMapFromServer( m_ui->cbServerSelector->currentText() );
}

void CMainWindow::loadThread_finished()
{
    m_ui->cbServerSelector->setEnabled( true );
    readyToDownload();

    CWorld::TShPtrWorld world = m_loader->getCurrentWorld();

    if( m_ui->leUserNickname->completer() == nullptr )
    {
        QCompleter* completer = new QCompleter(world->getAllPlayersName(), m_ui->leUserNickname);
        m_ui->leUserNickname->setCompleter( completer );
    }

    if( !world.isNull() )
    {
        if( !m_holder.m_worlds.contains( world ) )
            m_holder.m_worlds.push_back( world );
    }
}

void CMainWindow::readyToDownload()
{
    m_ui->pbLoadMap->setText(tr("Load server map"));
    m_ui->pbLoadMap->setEnabled(true);
}

void CMainWindow::on_cbServerSelector_currentIndexChanged(const QString &serverName)
{
    if( !m_holder.m_servers.value( serverName.mid( serverName.lastIndexOf(".")+1 ) ).value( serverName ) )
    {
        m_ui->pbLoadMap->setEnabled(false);
        m_ui->pbLoadMap->setText(tr("This server inactive"));
    }
    else
        readyToDownload();
    m_ui->leUserNickname->setCompleter( nullptr );
}

void CMainWindow::loadThread_unavailableServer()
{
    m_ui->cbServerSelector->setEnabled( true );
    const QString strServName = m_ui->cbServerSelector->currentText();
    const QString strServZone = strServName.mid( strServName.lastIndexOf(".")+1 );
    CDataHolder::TMapServerZoneAvailability currZone = m_holder.m_servers.value(strServZone);
    currZone.insert(strServName, false);
    m_holder.m_servers.insert(strServZone, currZone );
    on_cbServerSelector_currentIndexChanged( strServName );
}
