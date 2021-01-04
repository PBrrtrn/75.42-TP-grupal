#include <iostream>
#include <stdexcept>

//#include "server.h"

#include "client.h"

int main(const int argc, const char* argv[]) {
    Client client;
    client.startGame();
    //Server server;
    //server.start();
    //TODO chequear errores de parametros y excepciones generadas
    return 0;
}
