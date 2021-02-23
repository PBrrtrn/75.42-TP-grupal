#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QDrag>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) /*,currentMap(MapServer(1,1,1,1))*/
{
    ui->setupUi(this);

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

//void MainWindow::on_actionSave_triggered(){
//    this->openFile();

//}

void MainWindow::on_actionSaveAs_triggered(){
    this->saveFile();

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty()){
        std::ofstream foutMap(fileName.toUtf8().constData());
        //foutMap << this->currentMapGrid->getSerializedMap().c_str();
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

    qDebug(std::to_string(this->currentMapHeight).c_str());

    //MapServer newMap(this->currentMapWidth,this->currentMapHeight,this->currentMapMinPlayers,this->currentMapMaxPlayers);

    this->currentMap = new MapServer(this->currentMapWidth,this->currentMapHeight,this->currentMapMinPlayers,this->currentMapMaxPlayers);

    //GameMapGrid* mapGrid = new GameMapGrid(std::move(newMap),this->appStatus);
    GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);

    //this->currentMapGrid = mapGrid;

    qDebug("after current map grid");

    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(mapGrid);

    qDebug("after add item map grid");

    ui->gameMapView->setScene(scene);
    ui->gameMapView->setBackgroundBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
    //ui->gameMapView->setAcceptDrops(true);
    ui->gameMapView->show();
    this->repaint();

    qDebug("fin new map created");

}

void MainWindow::on_wallList_currentIndexChanged(int index)
{
    this->appStatus.setCurrentWallIndex(index);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    //std::string fileName = QFileDialog::getOpenFileName(this).toUtf8().constData();
    if (!fileName.isEmpty()){
        qDebug("before openfile assign map");
        //this->currentMap = MapServer(std::move(MapServer(fileName.toUtf8().constData())));
        qDebug("after openfile assign map");
        //GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);
        //MapServer newMap(MapServer(fileName.toUtf8().constData()));

        this->currentMap = new MapServer(fileName.toUtf8().constData());

        //GameMapGrid* mapGrid = new GameMapGrid(std::move(newMap),this->appStatus);

        GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);

        //this->currentMapGrid = mapGrid;

        QGraphicsScene* scene = new QGraphicsScene;
        scene->addItem(mapGrid);

        ui->gameMapView->setScene(scene);
        ui->gameMapView->setBackgroundBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
        ui->gameMapView->show();

    }

    this->repaint();

}



#if 0
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton
        /*&& iconLabel->geometry().contains(event->pos()) */ ) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText("a");
        drag->setMimeData(mimeData);
        //drag->setPixmap(iconPixmap);

        Qt::DropAction dropAction = drag->exec();
    }
}
#endif
