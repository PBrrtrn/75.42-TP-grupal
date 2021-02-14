#ifndef __MOVEMENT_STATE_H__
#define __MOVEMENT_STATE_H__

enum MovementState { 
	//tipos de mensaje desde cliente a servidor
	STATE_MOVING_FORWARD = 1,
	STATE_MOVING_BACKWARDS = 2,
	STATE_MOVING_LEFT = 3,
	STATE_MOVING_RIGHT = 4,
	STATE_NOT_MOVING = 5
};

#endif
