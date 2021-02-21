#ifndef GAMEMAPGRID_H
#define GAMEMAPGRID_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QMessageBox>
#include "../server_src/MapServer.h"
#include "texture_list.h"
#include "appstatus.h"

class GameMapGrid : public QGraphicsWidget
{
    Q_OBJECT
public:
    GameMapGrid(Map& map,AppStatus& appStatus,QGraphicsWidget *parent = nullptr);
    std::vector<std::vector<int>> map;
    void loadMap(MapServer& map);

private:
    AppStatus& appStatus;
    MapServer fullMap;


};

#endif // GAMEMAPGRID_H
