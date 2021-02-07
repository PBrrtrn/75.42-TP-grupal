#ifndef __CLIENT_MESSAGE_H_
#define __CLIENT_MESSAGE_H_

#include "MessageType.h"

struct ClientMessage {
	MessageType type;
	char entityId;
};

#endif
