#ifndef __DOOR_H__
#define __DOOR_H__

#include "../../common_src/Vector.h"

class Door{

    private:

        bool locked;
        bool open;
        int time_to_close;
        Vector location;

    public:

        Door(bool is_locked,int xGridLocation,int yGridLocation);

        bool isLocked();
        bool isOpen();
        int getTimeToClose();

        void openDoor();
        void unlockDoor();

        Vector getLocation();

        ~Door();

};

#endif
