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
    if (!fileName.isEmpty())
        Map map(fileName.toUtf8().constData());
        //addressWidget->writeToFile(fileName);
}

void MainWindow::newFile()
{
    NewMapWindow *nw = new NewMapWindow(this);
    nw->show();
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
        Map map(fileName.toUtf8().constData());
        GameMapGrid* mapGrid = new GameMapGrid(map,this->appStatus);

        QGraphicsScene* scene = new QGraphicsScene;
        scene->addItem(mapGrid);

        ui->gameMapView->setScene(scene);
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
