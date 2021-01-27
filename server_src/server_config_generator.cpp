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

	out << YAML::Key << "Ametralladora" ;
		out << YAML::BeginMap;
			out << YAML::Key << "Precision";
			out << YAML::Value << 10 ;
			out << YAML::Key << "Cadencia";
			out << YAML::Value << 0.1 ;
			out << YAML::Key << "Nombre";
			out << YAML::Value << "AMETRALLADORA" ;
			out << YAML::Key << "AttackRange";
			out << YAML::Value << 1000000 ;	
			out << YAML::Key << "Idx";
			out << YAML::Value << 2 ;			
		out << YAML::EndMap;

	out << YAML::Key << "CanionDeCadena" ;
		out << YAML::BeginMap;
			out << YAML::Key << "Nombre";
			out << YAML::Value << "CANION_DE_CADENA" ;
			out << YAML::Key << "AttackRange";
			out << YAML::Value << 1000000 ;	
			out << YAML::Key << "Idx";
			out << YAML::Value << 3 ;			
		out << YAML::EndMap;

	out << YAML::Key << "Cuchillo" ;
		out << YAML::BeginMap;
			out << YAML::Key << "Nombre";
			out << YAML::Value << "CUCHILLO" ;
			out << YAML::Key << "AttackRange";
			out << YAML::Value << 1000000 ;	
			out << YAML::Key << "Idx";
			out << YAML::Value << 0 ;			
		out << YAML::EndMap;
	
	out << YAML::Key << "LanzaCohetes" ;
		out << YAML::BeginMap;
			out << YAML::Key << "Nombre";
			out << YAML::Value << "LANZA_COHETES" ;
			out << YAML::Key << "AttackRange";
			out << YAML::Value << 1000000 ;	
			out << YAML::Key << "Idx";
			out << YAML::Value << 4 ;			
		out << YAML::EndMap;

	out << YAML::Key << "Pistola" ;
		out << YAML::BeginMap;
			out << YAML::Key << "Nombre";
			out << YAML::Value << "PISTOLA" ;
			out << YAML::Key << "AttackRange";
			out << YAML::Value << 1000000 ;	
			out << YAML::Key << "Idx";
			out << YAML::Value << 1 ;			
		out << YAML::EndMap;

	out << YAML::EndMap;

	std::ofstream fout("../server_config.yml");
	fout << out.c_str();
	fout.close();

    return 0;
}