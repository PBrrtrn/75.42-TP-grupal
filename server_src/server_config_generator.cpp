#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "./items/ItemSerializer.h"
#include "./games/DoorSerializer.h"
#include "./games/SpawnPointSerializer.h"
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
				out << YAML::Value << 0.1 ;
				out << YAML::Key << "RotationLeft";
				out << YAML::Value << 0.1 ;	
				out << YAML::Key << "RotationRight";
				out << YAML::Value << -0.1 ;			
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
	DoorSerializer doorSerializer;
	SpawnPointSerializer SPSerializer;
	std::vector<std::string> items;
	
	std::vector<std::string> doors;
	std::vector<std::string> spawnpoints;
	
	Food f(Vector(1,10),false);
	
	std::string itemSerialized = serializer.serialize(f);
	
	items.push_back(itemSerialized);
	
	Bullets b(Vector(5,1),false);
	itemSerialized = serializer.serialize(b);
	
	items.push_back(itemSerialized);	
	
	Door d(true,5,4);
	
	std::string doorSerialized = doorSerializer.serialize(d);
	
	doors.push_back(doorSerialized);
	
	Door d2(false,8,4);
	
	doorSerialized = doorSerializer.serialize(d2);
	
	doors.push_back(doorSerialized);

	SpawnPoint sp1(Vector(3,3), Vector(1,0));	
	std::string sp1Serialized = SPSerializer.serialize(sp1);
	SpawnPoint sp2(Vector(5,5), Vector(1,0));
	std::string sp2Serialized = SPSerializer.serialize(sp2);
	SpawnPoint sp3(Vector(10, 10), Vector(1,0));
	std::string sp3Serialized = SPSerializer.serialize(sp3);

	spawnpoints.push_back(sp1Serialized);
	spawnpoints.push_back(sp2Serialized);
	spawnpoints.push_back(sp3Serialized);
	
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
		
		outMap << YAML::Key << "doors";
		outMap << YAML::Value << YAML::Flow << doors;	
		
		outMap << YAML::Key << "spawnpoints";
		outMap << YAML::Value << YAML::Flow << spawnpoints;	

	outMap << YAML::EndMap;
	
	std::ofstream foutMap("../maps/map-test.yml");
	foutMap << outMap.c_str();
	foutMap.close();

	
	//reabro el mapa para asegurarme que no meti basura
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
			mensaje = "era un food!!";
		} 

		if (item.getType() == TYPE_BULLETS){
			mensaje = "eran bullets!!";
		} 
		
		std::cout << mensaje << std::endl;
		
	}
	
	std::vector<std::string> doorsReleidas = config["doors"].as<std::vector<std::string>>();
	
	for (auto x: doorsReleidas){
		std::cout << "elemento YML leido:" << x ;
		std::cout << std::endl;
		Door door(doorSerializer.deserialize(x));
		
		if (door.isLocked()) {
			std::cout << "es una puerta cerrada" << std::endl;
		}
		
		std::cout << "pos puerta: "
			<< std::to_string(door.getLocation().getXCoordinate()) << " - "
			<< std::to_string(door.getLocation().getYCoordinate()) << std::endl;

	}	
		

    return 0;
}
