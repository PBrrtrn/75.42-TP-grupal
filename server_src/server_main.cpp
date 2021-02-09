#include <iostream>
#include <fstream>
#include <stdexcept>

#include "server.h"

int main(const int argc, const char* argv[]) {
	
    Server s;
    s.start();
    return 0;
}
