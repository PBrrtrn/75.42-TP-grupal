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
    GameMapGrid(MapServer& map,AppStatus& appStatus,QGraphicsWidget *parent = nullptr);
    std::vector<std::vector<int>> map;
    //void loadMap(Map& map);

private:
    AppStatus& appStatus;
    MapServer& fullMap;


};

#endif // GAMEMAPGRID_H
