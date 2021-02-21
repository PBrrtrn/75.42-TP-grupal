#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "../../common_src/MessageType.h"

struct Request {
	MessageType type;
	int id;
};

#endif