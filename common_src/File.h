#include <fstream>
#include <string>

#ifndef __FILE_H__
#define __FILE_H__

class File {
	/* 
	Clase que encapsula las operaciones necesarias para trabajar con un archivo
	garantizando seguir RAII, abriendo el archivo en el constructor y cerrandolo
	en el destructor de la clase.																							*/
private:
	std::ifstream f;
public:
	explicit File(const char *filepath);
	~File();
	File(const File&) = delete;
	File& operator=(const File&) = delete;
	const bool hasLine();
	std::string getLine();
};

#endif
