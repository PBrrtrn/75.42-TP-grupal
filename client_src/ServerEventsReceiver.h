#ifndef __SERVER_EVENTS_RECEIVER_H__
#define __SERVER_EVENTS_RECEIVER_H__

#include "Thread.h"

class ServerEventsReceiver : public Thread {
private:
public:
  ServerEventsReceiver();
  ~ServerEventsReceiver();
  void run();
};

#endif