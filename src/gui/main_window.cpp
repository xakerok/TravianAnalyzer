#include "gui/main_window.h"
#include "ui_main_window.h"

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
    m_loaderThread->start();

    readyToDownload();
    m_ui->cbServerSelector->addItems( m_holder.getServersList() );
    m_ui->cbSearchSelector->setCurrentText("ts8.travian.ru");

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
    m_ui->pbLoadMap->setText(tr("Loading..."));
    m_loader->loadMapFromServer( m_ui->cbServerSelector->currentText() );
}

void CMainWindow::loadThread_finished()
{
    m_ui->pbLoadMap->setEnabled( true );
    readyToDownload();

    CWorld::TShPtrWorld world = m_loader->getCurrentWorld();
    if( !world.isNull() )
    {
        if( !m_holder.m_worlds.contains( world ) )
            m_holder.m_worlds.push_back( world );

    }
}

void CMainWindow::readyToDownload()
{
    m_ui->pbLoadMap->setText(tr("Load server map"));
}

void CMainWindow::on_cbServerSelector_currentIndexChanged(const QString &arg1)
{


}
