#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QStandardPaths>
#include <QDebug>
#include <QTreeView>
#include <QListView>
#include <QModelIndexList>
#include <QAction>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QProcess>

#include "adbfsmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateLocalPath(const QModelIndexList&);
    void changeLocalPath(const QModelIndex&);
    void toggleLocalTree(bool);
    void devConnect(bool);

private:
    Ui::MainWindow *ui;
    void setup();

    QFileSystemModel *localModel;
    AdbFsModel *devModel;

    AdbFsModel *createDevModel();

    bool devExec(QString, QStringList, QStringList&);


};
#endif // MAINWINDOW_H
