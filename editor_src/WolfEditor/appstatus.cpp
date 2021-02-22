#include "appstatus.h"

AppStatus::AppStatus()
{
    this->selectedWallIndex = 0;
}

void AppStatus::setCurrentWallIndex(int index){
    this->selectedWallIndex = index;

}
int AppStatus::getCurrentWallIndex(){
    return this->selectedWallIndex;

}
