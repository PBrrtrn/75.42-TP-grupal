#include <iostream>
#include <stdexcept>

#include "server.h"

int main(const int argc, const char* argv[]) {
    Server server;
    server.start();
    //TODO chequear errores de parametros y excepciones generadas
    return 0;
}
