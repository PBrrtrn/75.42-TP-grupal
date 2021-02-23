#include "mapview.h"

MapView::MapView(QWidget* w) : QGraphicsView(w)
{
    //this->setAcceptDrops(true);
}

void MapView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("mapview dragEnter");

    if (true){


        //QMessageBox msgBox;

        //msgBox.setText("hola, drop");
        //msgBox.exec();
        //event->setAccepted(true);
        event->acceptProposedAction();
        //event->ignore();
    }
}

//void MapView::dropEvent(QDropEvent *event)
//{

//    qDebug("mapview dropEvent");

    //QMessageBox msgBox;
    //msgBox.setText(event->mimeData()->text());
    //msgBox.setText("hola, drop");


    //msgBox.exec();
    //event->acceptProposedAction();
//    event->ignore();
//}
