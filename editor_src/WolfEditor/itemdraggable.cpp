#include "itemdraggable.h"

#include <QMessageBox>

ItemDraggable::ItemDraggable(QWidget* widget): QLabel(widget)
{
    //this->itemData = "a";
    this->setAcceptDrops(true);
}

void ItemDraggable::mousePressEvent(QMouseEvent *event)
{
    qDebug("drag and drop start");

    if (event->button() == Qt::LeftButton
        /*&& iconLabel->geometry().contains(event->pos()) */ ) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText(this->itemData.c_str());
        drag->setMimeData(mimeData);
        drag->setPixmap( QPixmap(QLatin1String(this->icon.c_str())).scaled(QSize(30,30)));

        Qt::DropAction dropAction = drag->exec();
    }
}

void ItemDraggable::dragEnterEvent(QDragEnterEvent *event)
{
    if (true){


        //QMessageBox msgBox;

        //msgBox.setText("hola, drop");
        //msgBox.exec();
        //event->setAccepted(true);
        event->acceptProposedAction();
    }
}

void ItemDraggable::dropEvent(QDropEvent *event)
{

    QMessageBox msgBox;
    msgBox.setText(event->mimeData()->text());
    //msgBox.setText("hola, drop");


    msgBox.exec();
    event->acceptProposedAction();
}
