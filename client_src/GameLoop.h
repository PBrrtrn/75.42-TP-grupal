#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "EventQueue.h"

class GameLoop {
private:
	EventQueue renderEventsQueue;
	/* renderEventsQueue es una cola protegida que puede ser accedida tanto por
	el thread del render como por el del serverReceiver. El renderer accede a
	la cola para desencolar eventos y renderizarlos, mientras que el
	serverEventsReceiver agrega eventos provenientes del servidor							 */
	BlockingQueue serverEventsReceiver;
	/* serverReceiver es por el momento una cola bloqueante que simula	el socket
		 del cual se recibirán las respuestas reales del servidor. Más	adelante va
		 a haber que cambiarlo para que sea un ServerSentEventsListener que maneje 
		 un objeto socket de verdad y reciba los eventos según los envía el servidor
		 real.

		 serverEventsReceiver corre sobre su propio thread y tiene una referencia a
		 renderEventsQueue, a donde encola las respuestas del servidor para que se
		 dibujen en la pantalla																								   */
	BlockingQueue clientEventsSender;
public:
	GameLoop();
	~GameLoop();
	void run();
};

#endif