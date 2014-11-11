#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "data_loader.h"
#include "data_holder.h"
#include "core/servers_model.h"

namespace Ui
{
class MainWindow;
}

class CMainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit CMainWindow(QWidget *parent = 0);
		~CMainWindow();

	private Q_SLOTS:
		void on_pbLoadMap_clicked();

		void loadThread_finished();

		void on_cbServerSelector_currentIndexChanged(const QString &serverName);

		void loadThread_unavailableServer();

	private:
		void readyToDownload();
	private:
		Ui::MainWindow *m_ui;
		CDataHolder m_holder;

		QSharedPointer<CDataLoader> m_loader;
		QSharedPointer<QThread> m_loaderThread;

		CServersModel* m_serversModel;
};

#endif // MAINWINDOW_H
