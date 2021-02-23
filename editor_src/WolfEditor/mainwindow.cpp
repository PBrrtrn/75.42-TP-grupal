#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QDrag>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),currentMap(MapServer(1,1))
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_botonArriba_clicked(){
//    this->setWindowTitle("hola");

//}

//void MainWindow::on_botonAbajo_clicked(){
//    this->setWindowTitle("chau");

//}

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
        foutMap << this->currentMap.getSerializedMap().c_str();
        foutMap.close();
    }
}

void MainWindow::newFile()
{
    NewMapWindow *nw = new NewMapWindow(this->currentMap,this);

    QObject::connect(nw, SIGNAL(newMapCreated()), this, SLOT(on_newMapCreated()));

    nw->move(200,200);
    nw->show();



}

void MainWindow::on_newMapCreated(){
    GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);

    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(mapGrid);

    ui->gameMapView->setScene(scene);
    ui->gameMapView->setBackgroundBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
    //ui->gameMapView->setAcceptDrops(true);
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
    //std::string fileName = QFileDialog::getOpenFileName(this).toUtf8().constData();
    if (!fileName.isEmpty()){
        this->currentMap = MapServer(fileName.toUtf8().constData());
        GameMapGrid* mapGrid = new GameMapGrid(this->currentMap,this->appStatus);

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
