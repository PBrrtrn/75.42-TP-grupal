#include "itemdraggable.h"

ItemDraggable::ItemDraggable(QWidget* widget): QLabel(widget)
{
    //this->itemData = "a";
}

void ItemDraggable::mousePressEvent(QMouseEvent *event)
{
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
