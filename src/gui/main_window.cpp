#include "gui/main_window.h"
#include "ui_main_window.h"

#include <QDebug>
#include <QCompleter>

CMainWindow::CMainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow),
	m_serversModel( new CServersModel( &m_holder, this ) )
{
	m_ui->setupUi(this);

	m_loaderThread = QSharedPointer<QThread>(new QThread);
	m_loader = QSharedPointer<CDataLoader>(new CDataLoader);

	m_loader->moveToThread( m_loaderThread.data() );
	m_loaderThread->start();

	bool bRes = connect( m_loader.data(), &CDataLoader::finished,
								this, &CMainWindow::loadThread_finished );
	Q_ASSERT( bRes );

	bRes = connect( m_loader.data(), &CDataLoader::serverUnavailable,
						 this, &CMainWindow::loadThread_unavailableServer );
	Q_ASSERT( bRes );

	readyToDownload();
	m_ui->cbServerSelector->setModel( m_serversModel );
	m_ui->cbServerSelector->setCurrentIndex(7);
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

//	m_ui->tabWidget->setCurrentWidget( m_ui->tabFile );
//	m_ui->listView->setModel( m_loader->getCurrentServer() );


}

void CMainWindow::readyToDownload()
{
	m_ui->pbLoadMap->setText(tr("Load server map"));
	m_ui->pbLoadMap->setEnabled(true);
}

void CMainWindow::on_cbServerSelector_currentIndexChanged(const QString &serverName)
{
	Q_UNUSED(serverName);

}

void CMainWindow::loadThread_unavailableServer()
{
	m_ui->cbServerSelector->setEnabled( true );
//	m_holder.
}
