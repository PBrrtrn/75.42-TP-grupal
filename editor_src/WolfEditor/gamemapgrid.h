#ifndef GAMEMAPGRID_H
#define GAMEMAPGRID_H

#include <QGraphicsWidget>
#include "Map.h"
#include "texture_list.h"
#include "appstatus.h"

class GameMapGrid : public QGraphicsWidget
{
    Q_OBJECT
public:
    GameMapGrid(Map& map,AppStatus& appStatus,QGraphicsWidget *parent = nullptr);
    std::vector<std::vector<int>> map;
    //void loadMap(Map& map);

private:
    AppStatus& appStatus;
    Map& fullMap;


};

#endif // GAMEMAPGRID_H
