#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setup();
    connect(ui->localExplorer, &QListView::indexesMoved, this, &MainWindow::updateLocalPath);
    connect(ui->localTreeToggleAct, &QAction::toggled, this, &MainWindow::toggleLocalTree);
    connect(ui->localTree, &QTreeView::expanded, this, &MainWindow::changeLocalPath);
    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::devConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup() {

    localModel = new QFileSystemModel;

    QString home = QStandardPaths::standardLocations(
                       QStandardPaths::HomeLocation).first();

    qDebug() << "Using home: " << home;

    localModel->setRootPath(home);

    ui->localTree->setModel(localModel);
    ui->localTree->setRootIndex(localModel->index(home));
    ui->localExplorer->setModel(localModel);
    ui->localExplorer->setRootIndex(localModel->index(home));

}

void MainWindow::updateLocalPath(const QModelIndexList &indexes) {
    qDebug() << "updating local path";
    qDebug() << indexes;
    ui->localExplorer->setRootIndex(indexes.first());
}

void MainWindow::toggleLocalTree(bool checked) {
    auto geometry = ui->localTree->geometry();
    int w = 100;
    geometry.setWidth(w * (int) checked);
    ui->localTree->setGeometry(geometry);
    //ui->gridLayout->update();
}

void MainWindow::changeLocalPath(const QModelIndex &index) {
    qDebug() << "Expanded " << index;
    ui->localExplorer->setRootIndex(index);
    //ui->localExplorer->setCurrentIndex(index);
}

/*QAbstractItemModel *MainWindow::createDevModel() {
    return new QAbstractItemModel() {

    };
}*/

bool MainWindow::devExec(QString cmd, QStringList args, QStringList &sl) {
    qDebug() << "Executing command [" << cmd << " " << args << "]";
    QProcess process;
    process.setProgram(cmd);
    process.setArguments(args);
    process.start();
    process.waitForFinished();
    auto output = process.readAllStandardOutput();
    //qDebug() << output;
    QString s = QString(output).trimmed();
    //qDebug() << s.trimmed();
    sl = QStringList(s.split('\n'));
    return process.exitCode() == 0;
}

void MainWindow::devConnect(bool checked) {
    QStringList out;
    int result = devExec("adb", QStringList() << "devices", out);
    if (!result || out.isEmpty()) {
        return;
    }
    out.removeFirst();
    qDebug() << "Creating dev fs model";
    devModel = new AdbFsModel(out);
    auto i = devModel->index(0, 0);
    qDebug() << "Setting model up into UI";
    qDebug() << "Using index " << i;
    ui->devTree->setModel(devModel);
    ui->devTree->setRootIndex(i);
    ui->devExplorer->setModel(devModel);
    ui->devExplorer->setRootIndex(i);
    ui->devTree->update();
    ui->devExplorer->update();
    qDebug() << "Connection finished";
}

