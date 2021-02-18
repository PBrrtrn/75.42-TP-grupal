#include "GameInputHandler.h"

const SDL_Keycode mapped_keys[] = { SDLK_w, SDLK_a, SDLK_s, SDLK_d };

GameInputHandler::GameInputHandler(ServerConnection& server_connection,
	BlockingQueue<MessageType>& message_queue) :
	// Todo: Sacar message_queue, que ServerConnection haga los bloqueos
		server_connection(server_connection), 
		message_queue(message_queue) 
		{ }

void GameInputHandler::handle(SDL_Event input) {
	if (input.key.repeat == 0) {
		//MessageType type;
		switch (input.type) {
		case (SDL_KEYDOWN) : 
			if (!this->keyboard_state.isDown(input.key.keysym.sym)) {
				switch (input.key.keysym.sym)
				{
				case SDLK_w:
					this->message_queue.push(TYPE_MOVE_FORWARD_START);
					this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/M_MOVE.wav", 0);
					break;
				case SDLK_a:
					this->message_queue.push(TYPE_MOVE_LEFT_START);
					break;
				case SDLK_s:
					this->message_queue.push(TYPE_MOVE_BACKWARD_START);
					this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/M_BACK.wav", 0);
					break;
				case SDLK_d:
					this->message_queue.push(TYPE_MOVE_RIGHT_START);
					break;
				case SDLK_SPACE:
					this->message_queue.push(TYPE_SHOOT_START);
					this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/DSSHOT.wav", 0);
					break;
				case SDLK_1:
					this->message_queue.push(TYPE_CHANGE_CUCHILLO);
					break;
				case SDLK_2:
					this->message_queue.push(TYPE_CHANGE_PISTOLA);
					break;
				case SDLK_3:
					this->message_queue.push(TYPE_CHANGE_AMETRALLADORA);
					break;
				case SDLK_4:
					this->message_queue.push(TYPE_CHANGE_CANION);
					break;
				case SDLK_5:
					this->message_queue.push(TYPE_CHANGE_LANZA_COHETES);
					break;
				default:
					//type = TYPE_UNDEFINED_KEY;
					break;
				}
				//this->message_queue.push(type);
			}
			this->keyboard_state.toggleKeyDown(input.key.keysym.sym);
		  	break;
		case (SDL_KEYUP) :
			if (this->keyboard_state.isDown(input.key.keysym.sym)) {
				switch (input.key.keysym.sym)
				{
				case SDLK_w:
					this->message_queue.push(TYPE_MOVE_FORWARD_STOP);
					break;
				case SDLK_a:
					this->message_queue.push(TYPE_MOVE_LEFT_STOP);
					break;
				case SDLK_s:
					this->message_queue.push(TYPE_MOVE_BACKWARD_STOP);
					break;
				case SDLK_d:
					this->message_queue.push(TYPE_MOVE_RIGHT_STOP);
					break;
				case SDLK_SPACE:
					this->message_queue.push(TYPE_SHOOT_STOP);
					break;
				default:
					//type = TYPE_UNDEFINED_KEY;
					break;
				}
				//this->message_queue.push(type);
			}
			this->keyboard_state.toggleKeyUp(input.key.keysym.sym);
		  	break;
	  	}
    }

}

void GameInputHandler::_playSound(const char* path, int loops) {
	int channel; 
	this->sound = Mix_LoadWAV(path);
	if (this->sound == NULL) printf("Loading sound error: %s\n", Mix_GetError());
	channel = Mix_PlayChannel(-1, this->sound, loops); 
}

GameInputHandler::~GameInputHandler() { 
	Mix_FreeChunk(this->sound);
}
