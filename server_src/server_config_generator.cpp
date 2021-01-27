#include <iostream>
#include <fstream>
#include <stdexcept>

#include "server.h"

int main(const int argc, const char* argv[]) {

	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Player" ;
		out << YAML::BeginMap;
			out << YAML::Key << "StartingHealth";
			out << YAML::Value << 20 ;
			out << YAML::Key << "MaxLives";
			out << YAML::Value << 3 ;
			out << YAML::Key << "MaxBullets";
			out << YAML::Value << 100 ;
			out << YAML::Key << "StartingBullets";
			out << YAML::Value << 8 ;			
		out << YAML::EndMap;
	out << YAML::EndMap;
	
	std::ofstream fout("../server_config.yml");
	fout << out.c_str();
	fout.close();

    return 0;
}
