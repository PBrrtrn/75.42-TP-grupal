#ifndef APPSTATUS_H
#define APPSTATUS_H


class AppStatus
{
private:
    int selectedWallIndex;
public:
    AppStatus();
    void setCurrentWallIndex(int index);
    int getCurrentWallIndex();

};

#endif // APPSTATUS_H
