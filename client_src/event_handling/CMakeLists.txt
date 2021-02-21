project(TPGrupal)

add_library(event-handling SHARED
	EventSender.cpp
	InputHandler.cpp
	GameInputHandler.cpp
	MenuInputHandler.cpp
	KeyboardState.cpp
	UpdateReceiver.cpp
)
