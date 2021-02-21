project(TPGrupal)

add_library(event-handling SHARED
	InputHandler.cpp
	MenuInputHandler.cpp
	GameInputHandler.cpp
	KeyboardState.cpp
	StatusUpdater.cpp
	GameStatusUpdater.cpp
	MenuStatusUpdater.cpp
	UpdateQueue.cpp
)
