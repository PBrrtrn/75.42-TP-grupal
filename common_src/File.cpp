#include <fstream>
#include <iostream>

#include "File.h"

File::File(const char *filepath) : f(filepath) {
	if (!this->f) throw std::runtime_error("Unable to open file");
}

File::~File() {
	(this->f).close();
}

const bool File::hasLine() {
	return (!this->f.eof());
}

std::string File::getLine() {
	std::string line;
	getline(this->f, line);
	return line;
}
