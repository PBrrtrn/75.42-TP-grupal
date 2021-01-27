#include <iostream>
#include <fstream>
#include <stdexcept>

#include "server.h"

int main(const int argc, const char* argv[]) {
	
	//YAML::Node config = YAML::LoadFile("../server_config.yml");
	
	//if (ServerConfig::Config["player"]["StartingHealth"]) {
	//  std::cout << ServerConfig::Config["player"]["StartingHealth"].as<std::string>() << "\n";
	//}	
	
	//YAML::Emitter out;
	//out << YAML::BeginMap;
	//out << YAML::Key << "player" << YAML::BeginMap;
	//out << YAML::Key << "StartingHealth";
	//out << YAML::Value << 20 << YAML::EndMap;
	//out << YAML::EndMap;
	
	//std::ofstream fout("../server_config.yml");
	//fout << out.c_str();
	//fout.close();
	
    Server s;
    s.start();
    
    
    //Client client;
    //client.startGame();
    //Server server;
    //server.start();
    //TODO chequear errores de parametros y excepciones generadas
    return 0;
}
