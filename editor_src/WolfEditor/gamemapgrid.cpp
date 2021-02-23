#include "gamemapgrid.h"
#include "layoutitem.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QMessageBox>

GameMapGrid::GameMapGrid(MapServer& map,AppStatus& appStatus,QGraphicsWidget *parent) : QGraphicsWidget(parent, Qt::Widget),appStatus(appStatus),fullMap(map)
{

    //this->fullMap = map;

    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);

    QGraphicsGridLayout *grid = new QGraphicsGridLayout(windowLayout);

    int width = this->fullMap.getWidth();
    int height = this->fullMap.getHeight();

    std::unordered_map<int,std::string> texture_list;

    for (int row = 0; row < height; row++){
        for (int column = 0;column < width; column++){

            std::string graphic = TextureList::textures.at(this->fullMap.getGridValue(column,row));
            LayoutItem *item = new LayoutItem(this->fullMap,this->appStatus,column,row,graphic,20);
            grid->addItem(item, row, column, 1, 1 );
        }
    }

    windowLayout->addItem(grid);


    setLayout(windowLayout);
    //this->setAcceptDrops(true);
    //setWindowTitle(tr("MapGrid"));

}

//void GameMapGrid::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (true){
//
//        QMessageBox msgBox;
//
//        msgBox.setText("hola, drop");
//        msgBox.exec();
//        event->setAccepted(true);
//        event->acceptProposedAction();
//    }
//}
