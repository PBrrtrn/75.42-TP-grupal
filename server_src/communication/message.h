#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>

class Message {

	private:

	std::string m;
	int clientId;	

	public:

	Message(std::string data,int clientId);
	
	std::string getMessage();
	int getClientId();
	
	~Message();


};

#endif
