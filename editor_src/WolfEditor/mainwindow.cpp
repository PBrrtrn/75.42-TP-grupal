#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QDrag>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("WolfEditor");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered(){
    this->newFile();
}

void MainWindow::on_actionOpen_triggered(){
    this->openFile();

}


void MainWindow::on_actionSaveAs_triggered(){
    this->saveFile();

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty()){
        std::ofstream foutMap(fileName.toUtf8().constData());
        foutMap << this->currentMap->getSerializedMap().c_str();
        foutMap.close();
    }
}

void MainWindow::newFile()
{
    NewMapWindow *nw = new NewMapWindow(this->currentMapWidth,this->currentMapHeight,this->currentMapMinPlayers,this->currentMapMaxPlayers,this);

    QObject::connect(nw, SIGNAL(newMapCreated()), this, SLOT(on_newMapCreated()));
    nw->move(200,200);
    nw->show();

}

void MainWindow::on_newMapCreated(){


    this->currentMap = new MapServer(this->currentMapWidth,this->currentMapHeight,this->currentMapMinPlayers,this->currentMapMaxPlayers);

    GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);


    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(mapGrid);


    ui->gameMapView->setScene(scene);
    ui->gameMapView->setBackgroundBrush(QBrush(Qt::lightGray,Qt::SolidPattern));

    ui->gameMapView->show();
    this->repaint();


}

void MainWindow::on_wallList_currentIndexChanged(int index)
{
    this->appStatus.setCurrentWallIndex(index);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){

        this->currentMap = new MapServer(fileName.toUtf8().constData());
        GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addItem(mapGrid);

        ui->gameMapView->setScene(scene);
        ui->gameMapView->setBackgroundBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
        ui->gameMapView->show();

    }

    this->repaint();

}
