#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "core/data_loader.h"
#include "core/data_holder.h"

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
};

#endif // MAINWINDOW_H
