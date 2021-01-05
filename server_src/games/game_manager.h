#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

////#include <vector>
#include "../communication/thread_client.h"

class GameManager{

private:
	//Game game; //aqui deberia haber un conjunto de Games, por ahora manejo uno.
	ThreadClient* c;

public:
	void addClient(ThreadClient& c);

#endif
