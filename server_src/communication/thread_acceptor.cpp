#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor() {}

void ThreadAcceptor:: run() {
	
	const YAML::Node& c = ServerConfig::Config["Server"];
	
	std::string host = c["Hostname"].as<std::string>();
	std::string port = c["Port"].as<std::string>();
	
	std::cout << "Running server on host: " << host << ",port: " << port << std::endl;
	
	bool resultado = this->socket.socket_bind_and_listen(host.c_str(),port.c_str());
	
	std::cout << "Acceptor socket opened:" << (resultado ? "OK" : "ERROR!") << std::endl;
	
    while (this->keep_running) {
        this->acceptConnection();
        this->gameManager.cleanUpDeadGames();
    }
}

void ThreadAcceptor::acceptConnection(){
	Socket peer;
	if (peer.socket_accept(this->socket) > 0) {
		this->gameManager.acceptClient(std::move(peer));
	}
}

void ThreadAcceptor::shutdown(){
	this->keep_running = false;
	this->socket.close_socket();
}

ThreadAcceptor:: ~ThreadAcceptor() {}
