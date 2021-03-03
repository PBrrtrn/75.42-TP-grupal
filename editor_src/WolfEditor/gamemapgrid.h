#ifndef GAMEMAPGRID_H
#define GAMEMAPGRID_H

#include <QGraphicsWidget>
#include "../../server_src/games/MapServer.h"
#include "texture_list.h"
#include "appstatus.h"

class GameMapGrid : public QGraphicsWidget
{
    Q_OBJECT
public:
    GameMapGrid(MapServer* map,AppStatus& appStatus,QGraphicsWidget *parent = nullptr);
    std::vector<std::vector<int>> map;
    std::string getSerializedMap();

private:
    AppStatus& appStatus;
    //MapServer& fullMap;
    MapServer* fullMap;
//    void dragEnterEvent(QDragEnterEvent *event);


};

#endif // GAMEMAPGRID_H
