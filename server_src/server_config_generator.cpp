#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "./items/ItemSerializer.h"
//#include "./items/food.h"

#include "server.h"

int main(const int argc, const char* argv[]) {

	YAML::Emitter out;	
	
	std::cout << "generate config file..." << std::endl;
	
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

		out << YAML::Key << "Moves" ;
			out << YAML::BeginMap;
				out << YAML::Key << "Step";
				out << YAML::Value << 5 ;
				out << YAML::Key << "RotationLeft";
				out << YAML::Value << 15 ;	
				out << YAML::Key << "RotationRight";
				out << YAML::Value << -15 ;			
		out << YAML::EndMap;

		out << YAML::Key << "Server" ;
			out << YAML::BeginMap;
				out << YAML::Key << "Hostname";
				out << YAML::Value << "localhost" ;
				out << YAML::Key << "Port";
				out << YAML::Value << "9000" ;		
			out << YAML::EndMap;

		out << YAML::Key << "Maps";
			out << YAML::BeginMap;
				out << YAML::Key << "Location";
				out << YAML::Value << "../maps/" ;
			out << YAML::EndMap;

		out << YAML::Key << "MapsSequence";
			out << YAML::BeginSeq; 
			out << "map1.yml";
			out << "map2.yml";
			out << YAML::EndSeq;

	out << YAML::EndMap;
	std::ofstream fout("../server_config.yml");
	fout << out.c_str();
	fout.close();
	
	std::cout << "generate example map..." << std::endl;
	
	//Generacion de un mapa:
	
	YAML::Emitter outMap;	
	
	std::vector<std::vector<int>> datos;
	
	ItemSerializer serializer;
	std::vector<std::string> items;
	
	Food f(Vector(1,10),false);
	
	std::string itemSerialized = serializer.serialize(f);
	
	items.push_back(itemSerialized);
	
	Bullets b(Vector(5,1),false);
	itemSerialized = serializer.serialize(b);
	
	items.push_back(itemSerialized);	
	
	//itemSerialized = "d,ef";
	
	//items.push_back(itemSerialized);	
	
	for (int i = 0; i < 16; i++)
		datos.push_back(std::vector<int>(16, i));
	
	outMap << YAML::BeginMap;
		outMap << YAML::Key << "minPlayers";
		outMap << YAML::Value << "2" ;	
		outMap << YAML::Key << "maxPlayers";
		outMap << YAML::Value << "20" ;	
		outMap << YAML::Key << "width";
		outMap << YAML::Value << "16" ;			
		outMap << YAML::Key << "height";
		outMap << YAML::Value << "16" ;		
		outMap << YAML::Key << "grid";
		outMap << YAML::Value << YAML::Flow << datos;		
		
		outMap << YAML::Key << "items";
		outMap << YAML::Value << YAML::Flow << items;		

	outMap << YAML::EndMap;
	
	std::ofstream foutMap("../maps/map-test.yml");
	foutMap << outMap.c_str();
	foutMap.close();

	std::cout << "reload example map and print grid..." << std::endl;
	YAML::Node config = YAML::LoadFile("../maps/map-test.yml");
	
	std::vector<std::vector<int>> datosFile = config["grid"].as<std::vector<std::vector<int>>>();
	
	for (auto x: datosFile){
		for (auto y: x){
				std::cout << y << "," ;
			}
		std::cout << std::endl;
	}
	
	std::vector<std::string> itemsReleidos = config["items"].as<std::vector<std::string>>();
	
	for (auto x: itemsReleidos){
		std::cout << "elemento YML leido:" << x ;
		std::cout << std::endl;
		Item item(serializer.deserialize(x));
		
		std::string mensaje = "no reconoci el item!!";
		
		if (item.getType() == TYPE_FOOD){
			std::cout << "era un food!!" << std::endl;
		} 

		if (item.getType() == TYPE_BULLETS){
			std::cout << "eran bullets!!" << std::endl;
		} 
		
		std::cout << mensaje << std::endl;
		
	}
		
	
	//std::cout << outMap.c_str() << std::endl;

    return 0;
}
